#include "fvemu.h"
#include "DefaultColors.h"

#define _BSD_SOURCE

#include <stdio.h>
#include <assert.h>
#include <string.h>


#ifndef unlikely
# define unlikely(x) __builtin_expect((x), 0)
#endif

#ifndef likely
# define likely(x) __builtin_expect((x), 1)
#endif

#define GETARG(S, n, def) (S->params[n] == 0 ? (def) : S->params[n])

#define CAP_MIN(val, vmin) do { \
    if((val) < (vmin)) val = vmin; \
} while(0)

#define CAP_MAX(val, vmax) do { \
    if((val) > (vmax)) val = vmax; \
} while(0)

#define CAP_MIN_MAX(val, vmin, vmax) do { \
    CAP_MIN(val, vmin); \
    CAP_MAX(val, vmax); \
} while(0)

#define PACK2(c1, c2) (((c1) << 8) | (c2))
#define PACK3(c1, c2, c3) (((c1) << 16) | ((c2) << 8) | (c3))
#define PACK4(c1, c2, c3, c4) (((c1) << 24) | ((c2) << 16) | ((c3) << 8) | (c4))

#define MODE(intermed, num) (((num) << 8) | (intermed))

#define APPLY_ATTR(ch) ((((uint16_t) S->cursorAttr) << 8) | (ch))

#define EMPTY_FIELD APPLY_ATTR(0x20)

#define APPLY_FLAG(mask, val) do { \
if(val) S->flags |= (mask); \
else S->flags &= ~(mask); \
} while(0)


#ifdef DEBUG
static const char * safeHex(uint32_t ch)
{
    // Remember, kids, always practice safe hex.
    static char buf[64];
    if(ch < 0x20) {
        snprintf(buf, sizeof(buf), "^%c", ch + 0x40);
    } else if(ch > 0x20 && ch < 0x7f) {
        snprintf(buf, sizeof(buf), "%c", ch);
    } else if(ch <= 0xff) {
        snprintf(buf, sizeof(buf), "%02x", ch);
    } else if(ch <= 0xffff) {
        int lo = ch & 0xff, hi = (ch >> 8) & 0xff;
        if(lo > 0x20 && lo < 0x7f && hi > 0x20 && hi < 0x7f) {
            snprintf(buf, sizeof(buf), "%c%c", hi, lo);
        } else {
            snprintf(buf, sizeof(buf), "%04x", ch);
        }
    }
    return buf;
}
#endif


static void row_fill(struct emuState *S, int row, int start, int count, uint16_t value)
{
    assert(row >= 0);
    assert(row < S->wRows);
    assert(start >= 0);
    assert(count >= 0);
    assert(start < S->wCols);
    assert(start + count <= S->wCols);

    struct termRow *r = S->rows[row];
#ifdef NOT_DARWIN
    // bah, we have to do this the hard way
    for(int i = 0; i < count; i++){
        r->chars[start + i] = value;
        //memcpy(r->chars + start+i, &value, 2);
    }
#else
    // memset_pattern8 is highly optimized on x86 :)
    memset_pattern8(&r->chars[start], &value, count * 8);
#endif
    r->flags |= TERMROW_DIRTY;
}


static void scroll_down(struct emuState *S, int top, int btm, int count)
{
    assert(count > 0);
    assert(top >= 0);
    assert(btm >= 0);
    assert(top < S->wRows);
    assert(btm < S->wRows);

    int clearStart;
    if(count > btm - top) {
        // every row's getting cleared, so we don't need to bother
        // changing the pointers at all!
        clearStart = top;
    } else {
        clearStart = btm - count + 1;
        struct termRow *keepBuf[count];
        memcpy(keepBuf, &S->rows[top],
               count * sizeof(struct termRow *));
        memmove(&S->rows[top], &S->rows[top + count],
                (clearStart - top) * sizeof(struct termRow *));
        memcpy(&S->rows[clearStart], keepBuf,
               count * sizeof(struct termRow *));
    }

    for(int i = clearStart; i <= btm; i++)
        row_fill(S, i, 0, S->wCols, EMPTY_FIELD);
}


static void scroll_up(struct emuState *S, int top, int btm, int count)
{
    assert(count > 0);
    assert(top >= 0);
    assert(btm >= 0);
    assert(top < S->wRows);
    assert(btm < S->wRows);

    // FIXME: this is unoptimized.
    while(count--) {
        struct termRow *movingRow = S->rows[btm];
        for(int i = btm; i > top; i--)
            S->rows[i] = S->rows[i - 1];
        S->rows[top] = movingRow;
        row_fill(S, top, 0, S->wCols, EMPTY_FIELD);
    }
}


static void cursor_index(struct emuState *S, int count)
{
    if(unlikely(count == 0)) return;

    if(likely(count > 0)) {
        // positive scroll - scroll down
        int dist = S->bScroll - S->cRow;
        if(dist >= count) {
            S->cRow += count;
        } else {
            S->cRow = S->bScroll;
            scroll_down(S, S->tScroll, S->bScroll, count - dist);
        }
    } else {
        count = -count; // scroll up
        int dist = S->cRow - S->tScroll;
        if(dist >= count)
            S->cRow -= count;
        else {
            S->cRow = S->tScroll;
            scroll_up(S, S->tScroll, S->bScroll, count - dist);
        }
    }
}

/*
static void do_BEL(struct emuState *S)
{
    //TerminalEmulator_bell(S);
}
*/


static void do_BS(struct emuState *S)
{
    S->cCol -= 1;
    CAP_MIN_MAX(S->cCol, 0, S->wCols - 1);
    S->wrapnext = 0;
}


static void do_CBT(struct emuState *S)
{
    int count = GETARG(S, 0, 1);
    for(;;) {
        S->cCol--;
        if(S->cCol <= 0) break;
        if(S->colFlags[S->cCol] & COLFLAG_TAB) {
            if(--count <= 0) break;
        }
    }
    CAP_MIN_MAX(S->cCol, 0, S->wCols - 1);
    S->wrapnext = 0;
}


static void do_CHA(struct emuState *S)
{
    int p1 = GETARG(S, 0, 1);
    S->cCol = p1 - 1;
    S->wrapnext = 0;
    CAP_MIN_MAX(S->cCol, 0, S->wCols - 1);
}


static void do_CHT(struct emuState *S)
{
    int count = GETARG(S, 0, 1);
    for(;;) {
        S->cCol++;
        if(S->cCol >= S->wCols) break;
        if(S->colFlags[S->cCol] & COLFLAG_TAB) {
            if(--count <= 0) break;
        }
    }
    CAP_MIN_MAX(S->cCol, 0, S->wCols - 1);
    S->wrapnext = 0;
}


static void do_CNL(struct emuState *S)
{
    int p1 = GETARG(S, 0, 1);
    cursor_index(S, p1);
    S->cCol = 0;
    S->wrapnext = 0;
}


static void do_CPL(struct emuState *S)
{
    int p1 = GETARG(S, 0, 1);
    cursor_index(S, -p1);
    S->cCol = 0;
    S->wrapnext = 0;
}


static void do_CR(struct emuState *S)
{
    S->cCol = 0;
    S->wrapnext = 0;
}


static void do_CSI(struct emuState *S)
{
    S->state = ST_CSI;
    S->paramPtr = S->paramVal = 0;
    S->intermed = 0;
    memset(S->params, 0, sizeof(S->params));
}


static void do_CUB(struct emuState *S)
{
    S->cCol -= GETARG(S, 0, 1);
    CAP_MIN_MAX(S->cCol, 0, S->wCols - 1);
    S->wrapnext = 0;
}


static void do_CUF(struct emuState *S)
{
    S->cCol += GETARG(S, 0, 1);
    CAP_MIN_MAX(S->cCol, 0, S->wCols - 1);
    S->wrapnext = 0;
}


static void do_CUU(struct emuState *S)
{
    int p1 = GETARG(S, 0, 1);
    int row = S->cRow;
    S->cRow -= p1;
    CAP_MIN_MAX(S->cRow, (row < S->tScroll) ? 0 : S->tScroll, S->wCols - 1);
    S->wrapnext = 0;
}


static void do_CUD(struct emuState *S)
{
    int p1 = GETARG(S, 0, 1);
    int row = S->cRow;
    S->cRow += p1;
    CAP_MIN_MAX(S->cRow, 0, (row > S->bScroll) ? S->wRows - 1 : S->bScroll);
    S->wrapnext = 0;
}


static void do_CUP_HVP(struct emuState *S)
{
    int p1 = GETARG(S, 0, 1);
    int p2 = GETARG(S, 1, 1);
    S->cRow = p1 - 1;
    S->cCol = p2 - 1;
    S->wrapnext = 0;
    if(S->flags & MODE_ORIGIN) {
        S->cRow += S->tScroll;
        CAP_MIN_MAX(S->cRow, S->tScroll, S->bScroll);
    } else {
        CAP_MIN_MAX(S->cRow, 0, S->wRows - 1);
    }
    CAP_MIN_MAX(S->cCol, 0, S->wCols - 1);
}

/*
static void do_DA(struct emuState *S)
{
    // VT100 with AVO
    //TerminalEmulator_writeStr(S, "\e[?1;2c");
}
*/


static void do_DA2(struct emuState *S)
{
    switch(GETARG(S, 0, 0)) {
        case 0:
            // FIXME: Decide on exact response format
            //TerminalEmulator_writeStr(S, "\e[>0;0;1c");
            break;
    }
}


static void do_DCH(struct emuState *S)
{
    int del = GETARG(S, 0, 1);
    CAP_MIN_MAX(del, 0, S->wCols);
    uint16_t *chars = S->rows[S->cRow]->chars;
    for(int i = S->cCol; i < S->wCols; i++) {
        int src = i + del;
        chars[i] = (src < S->wCols) ? chars[src] : EMPTY_FIELD;
    }
    S->rows[S->cRow]->flags |= TERMROW_DIRTY;
}


static void do_DECALN(struct emuState *S)
{
    for(int i = 0; i < S->wRows; i++)
        row_fill(S, i, 0, S->wCols, APPLY_ATTR('E'));
}


static void do_DECRC(struct emuState *S)
{
    S->cRow = S->saveRow;
    S->cCol = S->saveCol;
    S->wrapnext = 0;
    S->cursorAttr = S->saveAttr;
    S->charset = S->saveCharset;
    memcpy(S->charsets, S->saveCharsets, sizeof(S->charsets));

    /* VT500 spec specifies that these flags (and only these!) are restored. */
    APPLY_FLAG(MODE_ORIGIN,     S->saveFlags & MODE_ORIGIN);
    APPLY_FLAG(MODE_WRAPAROUND, S->saveFlags & MODE_WRAPAROUND);

    if(S->flags & MODE_ORIGIN)
        CAP_MIN_MAX(S->cRow, S->tScroll, S->bScroll);

    CAP_MAX(S->cRow, S->wRows - 1);
    CAP_MAX(S->cCol, S->wCols - 1);
}


static void do_DECSC(struct emuState *S)
{
    S->saveRow     = S->cRow;
    S->saveCol     = S->cCol;
    S->saveAttr    = S->cursorAttr;
    S->saveCharset = S->charset;
    S->saveFlags   = S->flags;
    memcpy(S->saveCharsets, S->charsets, sizeof(S->charsets));
}


static void do_DECSTBM(struct emuState *S)
{
    int p1 = GETARG(S, 0, 1);
    int p2 = GETARG(S, 1, 65535);
    CAP_MIN(p1, 1);
    CAP_MAX(p2, S->wRows);
    if(p2 > p1) { // confirmed: xterm ignores other STBMs
        S->tScroll = p1 - 1;
        S->bScroll = p2 - 1;
        S->cRow = (S->flags & MODE_ORIGIN) ? S->tScroll : 0;
        S->cCol = 0;
    }
}


static void do_DL(struct emuState *S)
{
    if(S->cRow >= S->tScroll && S->cRow <= S->bScroll)
        scroll_down(S, S->cRow, S->bScroll, GETARG(S, 0, 1));
}


static void do_DSR(struct emuState *S)
{
    char buf[32];
    int line;
    switch(GETARG(S, 0, 0)) {
        case 5:
            //TerminalEmulator_writeStr(S, "\x1b[0n"); // OK response
            break;

        case 6:
            line = S->cRow;
            if(S->flags & MODE_ORIGIN)
                line -= S->tScroll;
            snprintf(buf, sizeof(buf), "\x1b[%d;%dR", line + 1, S->cCol + 1);
            //TerminalEmulator_writeStr(S, buf);
            break;
    }
}


static void do_ECH(struct emuState *S)
{
    int count = GETARG(S, 0, 1);
    CAP_MAX(count, S->wCols - S->cCol);
    row_fill(S, S->cRow, S->cCol, count, EMPTY_FIELD);
}


static void do_ED(struct emuState *S)
{
    int p1 = GETARG(S, 0, 0);
    int from = 0;
    int to = S->wRows - 1;
    switch(p1) {
        default:
        case 0:
            from = S->cRow + 1;
            break;
        case 1:
            to = S->cRow - 1;
            break;
        case 2:
            break;
    }
    for(int i = from; i <= to; i++)
        row_fill(S, i, 0, S->wCols, EMPTY_FIELD);
    // ED erases partial lines too...
    if(p1 == 1)
        row_fill(S, S->cRow, 0, S->cCol + 1, EMPTY_FIELD);
    else if(p1 != 2) // 0 or default
        row_fill(S, S->cRow, S->cCol, S->wCols - S->cCol, EMPTY_FIELD);
}


static void do_EL(struct emuState *S)
{
    int from = 0;
    int to = S->wCols - 1;
    switch(GETARG(S, 0, 0)) {
        default:
        case 0:
            from = S->cCol;
            break;
        case 1:
            to = S->cCol;
            break;
        case 2:
            break;
    }
    row_fill(S, S->cRow, from, to - from + 1, EMPTY_FIELD);
}


static void do_ESC(struct emuState *S)
{
    S->intermed = 0;
    S->state = ST_ESC;
}


static void do_HPA(struct emuState *S)
{
    S->cCol = GETARG(S, 0, 1) - 1;
    CAP_MIN_MAX(S->cCol, 0, S->wCols - 1);
    S->wrapnext = 0;
}


static void do_HT(struct emuState *S)
{
    for(;;) {
        S->cCol++;
        if(S->cCol >= S->wCols) break;
        if(S->colFlags[S->cCol] & COLFLAG_TAB) break;
    }
    CAP_MIN_MAX(S->cCol, 0, S->wCols - 1);
    S->wrapnext = 0;
}


static void do_HTS(struct emuState *S)
{
    S->colFlags[S->cCol] |= COLFLAG_TAB;
}


static void do_ICH(struct emuState *S)
{
    int ins = GETARG(S, 0, 1);
    CAP_MIN_MAX(ins, 0, S->wCols);
    uint16_t *chars = S->rows[S->cRow]->chars;
    for(int i = S->wCols - 1; i >= S->cCol; i--) {
        int src = i - ins;
        chars[i] = (src >= S->cCol) ? chars[src] : EMPTY_FIELD;
    }
    S->rows[S->cRow]->flags |= TERMROW_DIRTY;
}


static void do_IL(struct emuState *S)
{
    if(S->cRow >= S->tScroll && S->cRow <= S->bScroll)
        scroll_up(S, S->cRow, S->bScroll, GETARG(S, 0, 1));
}


static void do_IND(struct emuState *S)
{
    cursor_index(S, 1);
}


static void do_NEL(struct emuState *S)
{
    cursor_index(S, 1);
    S->cCol = 0;
    S->wrapnext = 0;
}


static void do_NL(struct emuState *S)
{
    cursor_index(S, 1);
    if(S->flags & MODE_NEWLINE)
        S->cCol = 0;
    S->wrapnext = 0;
}

static void do_CRNL(struct emuState *S)
{
    do_NL(S);
    do_CR(S);
}

static void do_OSC(struct emuState *S)
{
    S->state = ST_OSC;
    S->paramPtr = S->paramVal = 0;
    S->intermed = 0;
    memset(S->oscBuf, 0, sizeof(S->oscBuf));
}


static void do_RI(struct emuState *S)
{
    cursor_index(S, -1);
}


static void do_SD(struct emuState *S)
{
    scroll_up(S, S->tScroll, S->bScroll, GETARG(S, 0, 1));
}


static void do_SGR(struct emuState *S)
{
    for(int i = 0; i < S->paramPtr; i++) {
        switch(S->params[i]) {
            case 0:
                S->cursorAttr = 0;
                break;

            case 1: // bold / increased intensity
                S->cursorAttr |= ATTR_BOLD;
                S->cursorAttr &= ~ATTR_FAINT;
                break;

            case 2: // faint / decreased intensity
                S->cursorAttr |= ATTR_FAINT;
                S->cursorAttr &= ~ATTR_BOLD;
                break;

            case 3: // italic
                S->cursorAttr |= ATTR_ITALIC;
                break;

            case 4: // single underline
                S->cursorAttr |= ATTR_UNDERLINE;
                break;

            case 5: // slow blink
            case 6: // fast blink (!)
                S->cursorAttr |= ATTR_BLINK;
                break;

            case 7: // negative image
                S->cursorAttr |= ATTR_REVERSE;
                break;

            case 8:
                S->cursorAttr |= ATTR_INVIS;
                break;

            case 9: // crossed out
                S->cursorAttr |= ATTR_STRIKE;
                break;

            // case 10 ... 19: alt fonts

            // case 20: fraktur?!

            case 21: // double underline
                S->cursorAttr |= ATTR_UNDERLINE;
                break;

            case 22: // unbold / unfaint
                S->cursorAttr &= ~(ATTR_BOLD | ATTR_FAINT);
                break;

            case 23: // un-italic / unFraktur
                S->cursorAttr &= ~ATTR_ITALIC;
                break;

            case 24: // un-underline ("derline"?)
                S->cursorAttr &= ~ATTR_UNDERLINE;
                break;

            case 25: // un-blink
                S->cursorAttr &= ~ATTR_BLINK;
                break;

            // case 26: unused

            case 27: // un-reverse
                S->cursorAttr &= ~ATTR_REVERSE;
                break;

            case 28:
                S->cursorAttr &= ~ATTR_INVIS;
                break;

            case 29: // un-crosssed-out
                S->cursorAttr &= ~ATTR_STRIKE;
                break;

            case 30 ... 37: // foreground colors
                S->cursorAttr &= ~ATTR_FG_MASK;
                S->cursorAttr |= ATTR_CUSTFG | (S->params[i] - 30);
                break;

            case 38: // extended FG
                if(++i >= S->paramPtr) break;
                if(S->params[i] != 5) break;
                if(++i >= S->paramPtr) break;
                S->cursorAttr &= ~ATTR_FG_MASK;
                S->cursorAttr |= ATTR_CUSTFG | (S->params[i] & 255);
                break;

            case 39: // default FG
                S->cursorAttr &= ~(ATTR_FG_MASK | ATTR_CUSTFG);
                break;

            case 40 ... 47: // background colors
                S->cursorAttr &= ~ATTR_BG_MASK;
                S->cursorAttr |= ATTR_CUSTBG | (S->params[i] - 40) << 8;
                break;

            case 48: // extended BG
                if(++i >= S->paramPtr) break;
                if(S->params[i] != 5) break;
                if(++i >= S->paramPtr) break;
                S->cursorAttr &= ~ATTR_BG_MASK;
                S->cursorAttr |= ATTR_CUSTBG | (S->params[i] & 255) << 8;
                break;

            case 49: // default FG
                S->cursorAttr &= ~(ATTR_BG_MASK | ATTR_CUSTBG);
                break;

            case 90 ... 97: // bright foreground colors (not in ECMA048)
                S->cursorAttr &= ~ATTR_FG_MASK;
                S->cursorAttr |= ATTR_CUSTFG | (8 + S->params[i] - 90);
                break;

            case 100 ... 107: // bright background colors (not in ECMA048)
                S->cursorAttr &= ~ATTR_BG_MASK;
                S->cursorAttr |= ATTR_CUSTBG | (8 + S->params[i] - 100) << 8;
                break;

#ifdef DEBUG
            default:
                printf("unhandled SGR %d\n", S->params[i]);
#endif
        }
    }
}


static void do_SO(struct emuState *S)
{
    // Switch to G1
    S->charset = S->charsets[1];
}


static void do_SI(struct emuState *S)
{
    // Switch to G0
    S->charset = S->charsets[0];
}


static void do_SU(struct emuState *S)
{
    scroll_down(S, S->tScroll, S->bScroll, GETARG(S, 0, 1));
}


static void do_TBC(struct emuState *S)
{
    switch(GETARG(S, 0, 0)) {
        case 0: // clear htab here
            S->colFlags[S->cCol] &= ~COLFLAG_TAB;
            break;

        case 1: // clear vtab here (unimpl)
        case 4: // clear all vtabs (unimpl)
            break;

        case 2: // clear all htabs on this line
            // Although ECMA048 implies that this is similar to Ps=3, neither
            // xterm nor rxvt implement it that way, and vttest specifically
            // ensures that it does not, describing it as a "no-op"!
            break;

        case 3: // clear all htabs
        case 5: // clear all tabs
            for(int i = 0; i < S->wCols; i++)
                S->colFlags[i] &= ~COLFLAG_TAB;
            break;
    }
}


static void do_VPA(struct emuState *S)
{
    S->cRow = GETARG(S, 0, 1) - 1;
    S->wrapnext = 0;
    if(S->flags & MODE_ORIGIN) {
        S->cRow += S->tScroll;
        CAP_MIN_MAX(S->cRow, S->tScroll, S->bScroll);
    } else {
        CAP_MIN_MAX(S->cRow, 0, S->wRows - 1);
    }
}


static void do_dterm_window(struct emuState *S)
{
    int p1 = GETARG(S, 0, 0);
    int p2 = GETARG(S, 1, 0);
    int p3 = GETARG(S, 2, 0);
    switch(p1) {
        case 0: // deiconify
        case 1: // iconify
        case 3: // move
            // not implemented
            break;

        case 4: // resize (pixels)
            // XXX
            break;

        case 5: // raise
        case 6: // lower
        case 7: // refresh
            // not implemented
            break;

        case 8: // resize (text)
            if(p2 >= 1 && p3 >= 1 && p2 <= 999 && p3 <= 999)
                emu_core_resize(S, p2, p3);
            break;

        case 9: // zoom
            // XXX
            break;

        case 11: // report state
            // XXX
            break;

        case 13: // report position
            // XXX
            break;

        case 14: // report size (pixels)
            // XXX
            break;

        case 18: // report size (chars)
            // XXX
            break;

        case 19: // report size II (chars)
            // XXX
            break;

        case 20: // report icon label
        case 21: // report title
            // XXX
            break;

        default:
            if(p1 >= 24 && p1 < 999) { // resize to lines (DECSLPP)
                emu_core_resize(S, p1, S->wCols);
            } else {
#ifdef DEBUG
                printf("unhandled xterm window manipulation %d\n", p1);
#endif
            }
    }
}


static void do_VT52_graphics_on(struct emuState *S)
{
    // A real VT52 had a different special graphics character set than the
    // VT100, but the VT100 didn't implement that. We'll err on the side
    // of emulating the VT100 here, since the VT52 is super-obscure, and
    // many of its characters aren't even available in Unicode.
    S->charset = '0';
}


static void do_VT52_graphics_off(struct emuState *S)
{
    S->charset = 'B';
}

/*
static void do_VT52_ident(struct emuState *S)
{
    // VT52 had a pretty simple ident string, in large part because it didn't
    // have the brains to send anything more complex.
    //TerminalEmulator_writeStr(S, "\e/Z");
}
*/

static void do_VT52_loc_start(struct emuState *S)
{
    // This is kind of a massive hack, but VT52 is weird enough that it's
    // probably not worth doing in any more general fashion.
    S->paramVal = 0;
    S->vt52Hack = 1;
    S->state = ST_ESC;
}


static void do_VT52_loc_continue(struct emuState *S, uint8_t ch)
{
    if(S->vt52Hack == 1) {
        // Save the location char and come back for the next one
        S->paramVal = ch;
        S->state = ST_ESC;
        S->vt52Hack = 2;
        return;
    }

    int line = S->paramVal - 0x20;
    if(S->flags & MODE_ORIGIN)
        line += S->tScroll;

    // VT52 spec says that the cursor does NOT move if the row is invalid.
    if(line >= 0 && line < S->wRows)
        S->cRow = line;

    S->cCol = ch - 0x20;
    CAP_MIN_MAX(S->cCol, 0, S->wCols - 1);

    S->vt52Hack = 0;
}


static void do_VT52_return(struct emuState *S)
{
    S->flags &= ~MODE_VT52;
}


static void do_VT52_tab(struct emuState *S)
{
    // The definition of a tab in the VT52 manual says that tabs after
    // column 72 should move a space to the right, instead of to the margin.

    if(S->cCol >= 72)
        S->cCol++;
    else
        do_HT(S);

    CAP_MIN_MAX(S->cCol, 0, S->wCols - 1);
    S->wrapnext = 0;
}



static void do_modes(struct emuState *S, int flag)
{
    for(int i = 0; i < S->paramPtr; i++) {
        switch(MODE(S->intermed, S->params[i])) {

            case MODE(0, 4): // IRM (insert/replace mode)
                APPLY_FLAG(MODE_INSERT, flag);
                break;

            case MODE(0, 20): // LNM (normal linefeed mode)
                APPLY_FLAG(MODE_LINEFEED, flag);
                break;

            case MODE('?', 1): // DECCKM (cursor key mode)
                APPLY_FLAG(MODE_CURSORKEYS, flag);
                break;

            case MODE('?', 2): // DECANM (vt52 mode)
                if(flag == 0) { // this flag is weirdly inverted.
                    S->flags |= MODE_VT52;
                    S->charset = 'B';
                    S->vt52Hack = 0;
                }
                break;

            case MODE('?', 3): // DECCOLM (132/80 switch)
                if(!(S->flags & MODE_ALLOW_DECCOLM)) break;
                emu_core_resize(S, S->wRows, flag ? 132 : 80);
                // clear screen and reset cursor to 0/0
                for(int i = 0; i < S->wRows; i++)
                    row_fill(S, i, 0, S->wCols, EMPTY_FIELD);
                S->cCol = 0;
                S->cRow = (S->flags & MODE_ORIGIN) ? S->tScroll : 0;
                break;

            case MODE('?', 4): // DECSCLM (smooth scrolling)
                // Ignored - we don't implement this feature
                break;

            case MODE('?', 5): // DECSCNM (reverse video)
                APPLY_FLAG(MODE_INVERT, flag);
                for(int i = 0; i < S->wRows; i++)
                    S->rows[i]->flags |= TERMROW_DIRTY; // redraw everything!
                break;

            case MODE('?', 6): // DECOM (origin mode)
                APPLY_FLAG(MODE_ORIGIN, flag);
                // Origin flag homes the cursor when set/reset
                S->cRow = flag ? S->tScroll : 0;
                S->cCol = 0;
                break;

            case MODE('?', 7): // DECAWM (wraparound mode)
                APPLY_FLAG(MODE_WRAPAROUND, flag);
                break;

            case MODE('?', 8): // DECARM (autorepeat mode)
                // Ignored - neither of these make sense on a software terminal.
                break;

            case MODE('?', 9): // DECINLM (interlace) / X10 mouse tracking
                // DECINLM makes no sense on a software terminal.
                // Mouse tracking does, so we'll do that instead.
                S->flags &= ~MODE_MOUSE_MASK;
                APPLY_FLAG(MODE_MOUSE_X10, flag);
                break;

            case MODE('?', 12): // cursor blink
                // TODO
                break;

            case MODE('?', 25): // visible cursor
                APPLY_FLAG(MODE_SHOWCURSOR, flag);
                break;

            case MODE('?', 40): // allow DECCOLM
                // not quite sure what the point of this is, but what the hey.
                APPLY_FLAG(MODE_ALLOW_DECCOLM, flag);
                break;

            case MODE('?', 41): // more(1) fix
                // obsolete and ignored
                break;

            case MODE('?', 42): // DECNCRM
                // TODO
                break;

            case MODE('?', 45): // reverse wraparound
                APPLY_FLAG(MODE_REVWRAP, flag);
                break;

            case MODE('?', 1000): // mouse tracking
                S->flags &= ~MODE_MOUSE_MASK;
                APPLY_FLAG(MODE_MOUSE_1000, flag);
                break;

            case MODE('?', 1001):
                S->flags &= ~MODE_MOUSE_MASK;
                APPLY_FLAG(MODE_MOUSE_1001, flag);
                break;

            case MODE('?', 1002):
                S->flags &= ~MODE_MOUSE_MASK;
                APPLY_FLAG(MODE_MOUSE_1002, flag);
                break;

            case MODE('?', 1003):
                S->flags &= ~MODE_MOUSE_MASK;
                APPLY_FLAG(MODE_MOUSE_1003, flag);
                break;

            case MODE('?', 1047): // alternate buffer
            case MODE('?', 1049): // alternate buffer/cursor
                // TODO
                break;

#ifdef DEBUG
            default:
                printf("unhandled mode %x/%d (flag: %d)\n",
                       S->intermed, S->params[i], flag);
#endif
        }
    }
}


static void do_SM(struct emuState *S)
{
    do_modes(S, 1);
}


static void do_RM(struct emuState *S)
{
    do_modes(S, 0);
}



#define CASE(frm, to) case frm: to(S); break
#define CASE2(frm, frm2, to) CASE(PACK2(frm, frm2), to)

static void emu_ops_do_ctrl(struct emuState *S, uint8_t ch)
{
    switch(ch) {
            //CASE(0x05, do_ENQ);
            //CASE(0x07, do_BEL);
            CASE(0x08, do_BS);
            CASE(0x09, do_HT);
            CASE(0x0A, do_CRNL);
            CASE(0x0B, do_NL); // VT -> NL
            CASE(0x0C, do_NL); // NP -> NL
            CASE(0x0D, do_CR);
            CASE(0x0E, do_SO);
            CASE(0x0F, do_SI);

            CASE(0x1B, do_ESC);

#ifdef DEBUG
        default:
            printf("Unknown control char %s\n", safeHex(ch));
#endif
    }
}


static void emu_ops_do_esc(struct emuState *S, uint8_t lastch)
{
    // Ugh, this bit grinds my gears.
    switch(S->intermed) {
        case '(':
            S->charsets[0] = lastch;
            return;
        case ')':
            S->charsets[1] = lastch;
            return;
        case '*':
            S->charsets[2] = lastch;
            return;
        case '+':
            S->charsets[3] = lastch;
            return;
        default:
            break;
    }

    switch(PACK2(S->intermed, lastch)) {
            CASE('7', do_DECSC);
            CASE('8', do_DECRC);

            //CASE('=', do_DECPAM);
            //CASE('>', do_DECPNM);

            // note: anything from 0x40-0x7f is duplicated in C1 (0x80-0x9f)
            CASE('D', do_IND);
            CASE('E', do_NEL);
            CASE('H', do_HTS);
            CASE('M', do_RI);
            //CASE('N', do_SS2);
            //CASE('O', do_SS3);
            //CASE('P', do_DCS);
            //CASE('V', do_SPA);
            //CASE('W', do_EPA);
            //CASE('X', do_SOS);
            //CASE('Z', do_DECID);
            CASE('[', do_CSI);
            //CASE('\\', do_ST);
            CASE(']', do_OSC);
            //CASE('^', do_PM);
            //CASE('_', do_APC);

            // Extended ESC ops
            CASE2('#', '8', do_DECALN);

#ifdef DEBUG
        default:
            printf("unknown ESC %s\n", safeHex(PACK2(S->intermed, lastch)));
            break;
#endif
    }
}


static void emu_ops_do_c1(struct emuState *S, uint8_t lastch)
{
    switch(lastch) {
            CASE(0x84, do_IND);
            CASE(0x85, do_NEL);
            CASE(0x88, do_HTS);
            CASE(0x8D, do_RI);
            //CASE(0x8E, do_SS2);
            //CASE(0x8F, do_SS3);
            //CASE(0x90, do_DCS);
            //CASE(0x96, do_SPA);
            //CASE(0x97, do_EPA);
            //CASE(0x98, do_SOS);
            //CASE(0x9A, do_DECID);
            CASE(0x9B, do_CSI);
            //CASE(0x9C, do_ST);
            CASE(0x9D, do_OSC);
            //CASE(0x9E, do_PM);
            //CASE(0x9F, do_APC);

#ifdef DEBUG
        default:
            printf("unknown C1 %02x\n", lastch);
            break;
#endif
    }
}


static void emu_ops_do_csi(struct emuState *S, uint8_t lastch)
{
    switch(PACK2(S->intermed, lastch)) {
            CASE('@', do_ICH);
            CASE('A', do_CUU);
            CASE('B', do_CUD);
            CASE('C', do_CUF);
            CASE('D', do_CUB);
            CASE('E', do_CNL);
            CASE('F', do_CPL);
            CASE('G', do_CHA);
            CASE('H', do_CUP_HVP);
            CASE('I', do_CHT);
            CASE('J', do_ED);
            CASE('K', do_EL);
            CASE('L', do_IL);
            CASE('M', do_DL);
            CASE('P', do_DCH);
            CASE('S', do_SU);
            CASE('T', do_SD);
            CASE('X', do_ECH);
            CASE('Z', do_CBT);
            CASE('`', do_HPA);
            //CASE('b', do_REP); (ugh!)
            //CASE('c', do_DA);
            CASE2('>', 'c', do_DA2);
            //CASE2('=', 'c', do_DA3);
            CASE('d', do_VPA);
            CASE('f', do_CUP_HVP);
            CASE('g', do_TBC);
            CASE('h', do_SM);
            CASE2('?', 'h', do_SM);
            //CASE('i', do_MC);
            //CASE2('?', 'i', do_DECMC);
            CASE('l', do_RM);
            CASE2('?', 'l', do_RM);
            CASE('m', do_SGR);
            CASE('n', do_DSR);
            //CASE2('?', 'n', do_DECDSR);
            //CASE2('!', 'p', do_DECSTR);
            //CASE2('"', 'p', do_DECSCL);
            //CASE2('"', 'q', do_DECSCA);
            CASE('r', do_DECSTBM);
            //CASE2('?', 'r', DEC mode restore
            //CASE2('?', 's', DEC mode save
            CASE('t', do_dterm_window);
            //CASE2(0x27, 'w', do_DECEFR);
            //CASE2('&', 'w', do_DECLRP);
            //CASE('x', do_DECREQTPARM);
            //CASE2(0x27, 'z', do_DECELR);
            //CASE2(0x27, '{', do_DECSLE);
            //CASE2(0x27, '|', do_DECRQLP);

#ifdef DEBUG
        default:
            printf("unhandled CSI");
            if(S->paramPtr > 0)
                printf(" %d", S->params[0]);
            for(int i = 1; i < S->paramPtr; i++)
                printf("; %d", S->params[i]);
            printf(" %s\n", safeHex(PACK2(S->intermed, lastch)));
#endif
    }
}

/*
static void emu_ops_do_osc(struct emuState *S, int op)
{
    switch(op) {
        case 0: // xterm: set icon name and window title
            //case 1: // xterm: set icon name
        case 2: // xterm: set window title
            //TerminalEmulator_setTitle(S, S->oscBuf);
            break;

#ifdef DEBUG
        default:
            printf("unhandled OSC %d; '%s'\n", op, S->oscBuf);
#endif
    }
}
*/

static void emu_ops_do_vt52_ctrl(struct emuState *S, uint8_t ch)
{
    switch(ch) {
            //CASE(0x07, do_BEL);
            CASE(0x08, do_BS);
            CASE(0x09, do_VT52_tab);
            CASE(0x0a, do_IND);
            CASE(0x0d, do_NEL);
            CASE(0x1b, do_ESC);

#ifdef DEBUG
        default:
            printf("Unknown VT52 control char %s\n", safeHex(ch));
#endif
    }
}


static void emu_ops_do_vt52_esc(struct emuState *S, uint8_t ch)
{
    // VT52 locator mode. Hackety hack.
    if(S->vt52Hack > 0) {
        do_VT52_loc_continue(S, ch);
        return;
    }

    // A lot of VT52 operations behave like a VT100 equivalent with all params
    // zero, so we can use this as a shortcut:
    memset(S->params, 0, sizeof(S->params));

    switch(ch) {
            CASE('A', do_CUU);
            CASE('B', do_CUD);
            CASE('C', do_CUF);
            CASE('D', do_CUB);
            CASE('F', do_VT52_graphics_on);
            CASE('G', do_VT52_graphics_off);
            CASE('H', do_CUP_HVP);
            CASE('I', do_RI);
            CASE('J', do_ED);
            CASE('K', do_EL);

            CASE('Y', do_VT52_loc_start);
            //CASE('Z', do_VT52_ident);

            //CASE('=', do_VT52_altkeypad_on);
            //CASE('>', do_VT52_altkeypad_off);

            CASE('<', do_VT52_return);

#ifdef DEBUG
        default:
            printf("Unhandled VT52 ESC %c\n", ch);
#endif
    }
}


static void do_unichar(struct emuState *S, uint16_t uc)
{
    if(unlikely(S->wrapnext)) {
        if(S->flags & MODE_WRAPAROUND) {
            S->rows[S->cRow]->flags |= TERMROW_WRAPPED;
            cursor_index(S, 1);
            S->cCol = 0;
        }
        S->wrapnext = 0;
    }

    assert(S->cRow >= 0);
    assert(S->cCol >= 0);
    assert(S->cRow < S->wRows);
    assert(S->cCol < S->wCols);

    // simplify alias analysis for the compiler by putting this in a variable
    struct termRow *thisRow = S->rows[S->cRow];

    if(unlikely(S->flags & MODE_INSERT)) {
        int toMove = S->wCols - S->cCol - 1;
        if(toMove > 0) {
            memmove(&thisRow->chars[S->cCol + 1], &thisRow->chars[S->cCol], toMove);
        }
    }

    thisRow->chars[S->cCol++] = APPLY_ATTR(uc);
    thisRow->flags |= TERMROW_DIRTY;

    if(unlikely(S->cCol == S->wCols)) {
        S->cCol = S->wCols - 1;
        S->wrapnext = 1;
    }
}


static void unwind_utf8(struct emuState *S)
{
    switch(S->utf8state) {
        case 1:
        case 2:
        case 4:
            do_unichar(S, S->utf8buf[0]);
            break;

        case 3:
        case 5:
            do_unichar(S, S->utf8buf[1]);
            do_unichar(S, S->utf8buf[0]);
            break;

        case 6:
            do_unichar(S, S->utf8buf[2]);
            do_unichar(S, S->utf8buf[1]);
            do_unichar(S, S->utf8buf[0]);
            break;
    }
    S->utf8state = 0;
}


static uint16_t decsgr[32] = {
    0x0020, // SPACE
    0x25C6, // BLACK DIAMOND
    0x2592, // MEDIUM SHADE
    0x2409, // SYMBOL FOR HORIZONTAL TAB
    0x240C, // SYMBOL FOR FORM FEED
    0x240D, // SYMBOL FOR CARRIAGE RETURN
    0x240A, // SYMBOL FOR LINE FEED
    0x00B0, // DEGREE SIGN
    0x00B1, // PLUS-MINUS SIGN
    0x2424, // SYMBOL FOR NEWLINE
    0x240B, // SYMBOL FOR VERTICAL TABULATION
    0x2518, // BOX DRAWINGS LIGHT UP AND LEFT
    0x2510, // BOX DRAWINGS LIGHT DOWN AND LEFT
    0x250C, // BOX DRAWINGS LIGHT DOWN AND RIGHT
    0x2514, // BOX DRAWINGS LIGHT UP AND RIGHT
    0x253C, // BOX DRAWINGS LIGHT VERTICAL AND HORIZONTAL
    0x23BA, // HORIZONTAL SCAN LINE-1
    0x23BB, // HORIZONTAL SCAN LINE-3
    0x2500, // BOX DRAWINGS LIGHT HORIZONTAL
    0x23BC, // HORIZONTAL SCAN LINE-7
    0x23BD, // HORIZONTAL SCAN LINE-9
    0x251C, // BOX DRAWINGS LIGHT VERTICAL AND RIGHT
    0x2524, // BOX DRAWINGS LIGHT VERTICAL AND LEFT
    0x2534, // BOX DRAWINGS LIGHT UP AND HORIZONTAL
    0x252C, // BOX DRAWINGS LIGHT DOWN AND HORIZONTAL
    0x2502, // BOX DRAWINGS LIGHT VERTICAL
    0x2264, // LESS-THAN OR EQUAL TO
    0x2265, // GREATER-THAN OR EQUAL TO
    0x03C0, // GREEK SMALL LETTER PI
    0x2260, // NOT EQUAL TO
    0x00A3, // POUND SIGN
    0x00B7, // MIDDLE DOT
};


static void emu_ops_text(struct emuState * restrict S, const uint8_t *bytes, size_t len)
{
    if(len == 0) {
        unwind_utf8(S);
        return;
    }

    for(size_t i = 0; i < len; i++) {
        uint8_t c = bytes[i];

        // DEC linedrawing charset
        if(S->charset == '0' && (c >= 0x5f && c < 0x7f)) {
            do_unichar(S, decsgr[c - 0x5f]);
            continue;
        }

        // UK charset
        if(S->charset == 'A' && c == '$') {
            do_unichar(S, 0x00A3); // pound symbol
            continue;
        }

        if(unlikely(S->utf8state > 0)) {
            if(c < 0x80 || c >= 0xc0) {
                unwind_utf8(S);
            } else {
                switch(S->utf8state) {
                    case 1: // process 2/2
                        //do_unichar(S, ((S->utf8buf[0] & 0x3f) << 6)
                        //           |   (c & 0x3f));
                        do_unichar(S, (c << 8) | S->utf8buf[0]);
                        S->utf8state = 0;
                        break;

                    case 3: // process 3/3
                        do_unichar(S, ((S->utf8buf[0] & 0x1f) << 12)
                                   |  ((S->utf8buf[1] & 0x3f) << 6)
                                   |   (c & 0x3f));
                        S->utf8state = 0;
                        break;

                    case 6: // process 4/4
                        do_unichar(S, ((S->utf8buf[0] & 0x0f) << 18)
                                   |  ((S->utf8buf[1] & 0x3f) << 12)
                                   |  ((S->utf8buf[2] & 0x3f) << 6)
                                   |   (c & 0x3f));
                        S->utf8state = 0;
                        break;

                    case 2: // process 2/3
                    case 4: // process 2/4
                        S->utf8buf[1] = c;
                        S->utf8state++;
                        break;

                    case 5: // process 3/4
                        S->utf8buf[2] = c;
                        S->utf8state++;
                        break;
                }
                continue;
            }
        }

        if(likely(c < 0x80)) {
            // Just plain ASCII
            do_unichar(S, c);
        } else if(c < 0xc2) {
            // Invalid UTF8, valid ISO8859-1
            do_unichar(S, c);
        } else if(c < 0xe0) {
            // First character of 2-byte sequence
            S->utf8buf[0] = c;
            S->utf8state = 1;
        } else if(c < 0xf0) {
            // First character of 3-byte sequence
            S->utf8buf[0] = c;
            S->utf8state = 2;
        } else if(c < 0xf5) {
            // First character of 4-byte sequence
            S->utf8buf[0] = c;
            S->utf8state = 4;
        } else {
            // Invalid UTF8, valid ISO8859-1
            do_unichar(S, c);
        }
    }
}


void emu_term_reset(struct emuState *S)
{
    S->state = ST_GROUND;
    S->utf8state = 0;

    for(int i = 0; i < 258; i++)
        S->palette[i] = (default_colormap[i] << 8) | 0xff;

    S->cRow = S->cCol = S->saveRow = S->saveCol = 0;

    S->tScroll = 0;
    S->bScroll = S->wRows - 1;

    S->flags = MODE_WRAPAROUND | MODE_SHOWCURSOR | MODE_ALLOW_DECCOLM;
    S->cursorAttr = S->saveAttr = 0;

    S->charset = 0;
    for(int i = 0; i < 4; i++)
        S->charsets[i] = 'B'; // USASCII

    for(int i = 0; i < S->wRows; i++)
        row_fill(S, i, 0, S->wCols, EMPTY_FIELD);

    for(int i = 0; i < S->wCols; i++) {
        if(i % 8 == 7)
            S->colFlags[i] |= COLFLAG_TAB;
    }
}


static void allocBackBuffers(struct emuState *S)
{
    size_t rowSize = sizeof(struct termRow) + sizeof(uint16_t) * S->wCols;
    S->rowBase = calloc(S->wRows, rowSize);
    S->rows = calloc(S->wRows, sizeof(struct termRow *));
    S->colFlags = calloc(S->wCols, sizeof(uint8_t));

    for(int i = 0; i < S->wRows; i++)
        S->rows[i] = S->rowBase + i * rowSize;
}


struct emuState * emu_core_init(int rows, int cols)
{
    struct emuState *S;
    S = malloc(sizeof(struct emuState));
    S->wRows = rows;
    S->wCols = cols;
    S->cCol = 0;
    S->cRow = 0;

    allocBackBuffers(S);
    emu_term_reset(S);

    return S;
}


void emu_core_resize(struct emuState *S, int rows, int cols)
{
    struct termRow **old_rows = S->rows;
    uint8_t *old_colFlags = S->colFlags;
    void *old_rowBase = S->rowBase;

    int old_wRows = S->wRows, old_wCols = S->wCols;

    S->wRows = rows;
    S->wCols = cols;

    allocBackBuffers(S);
    emu_term_reset(S);

    // FIXME: Improve this.
    for(int r = 0; r < rows && r < old_wRows; r++) {
        for(int c = 0; c < cols && c < old_wCols; c++)
            S->rows[r]->chars[c] = old_rows[r]->chars[c];
        S->rows[r]->flags = TERMROW_DIRTY;
    }

    //for(int r = 0; r < old_wRows; r++)
    //    TerminalEmulator_freeRowBitmaps(old_rows[r]);
    free(old_rows);
    free(old_colFlags);
    free(old_rowBase);

    //TerminalEmulator_resize(S);
}


void emu_core_free(struct emuState *S)
{
    //for(int r = 0; r < S->wRows; r++)
    //    TerminalEmulator_freeRowBitmaps(S->rows[r]);

    free(S->rowBase);
    free(S->rows);
    free(S->colFlags);
    free(S);
}


size_t emu_core_run(struct emuState *S, const uint8_t *bytes, size_t len)
{
    int first_ground = -1, ground_len = 0;

#define GROUND_FLUSH() do { \
    if(first_ground >= 0) { \
        emu_ops_text(S, bytes + first_ground, ground_len); \
        first_ground = -1; \
    } \
} while(0)

#define UTF8_FLUSH() emu_ops_text(S, NULL, 0)

    for(size_t i = 0; i < len; i++) {
        uint8_t ch = bytes[i];

        if(unlikely(S->flags & MODE_VT52)) {
            if(ch < 0x20) {
                GROUND_FLUSH();
                UTF8_FLUSH();
                emu_ops_do_vt52_ctrl(S, ch);
                continue;
            }
        } else {
            if(ch < 0x20 && S->state != ST_OSC) {
                GROUND_FLUSH();
                UTF8_FLUSH();
                emu_ops_do_ctrl(S, ch);
                continue;
            }

            // C1 control characters, but only when not in UTF8 sequences
            if(ch >= 0x80 && ch < 0xA0) {
                GROUND_FLUSH();
                if(S->state == ST_GROUND && S->utf8state == 0) {
                    UTF8_FLUSH();
                    emu_ops_do_c1(S, ch);
                    S->state = ST_GROUND; // FIXME: check this
                    continue;
                }
            }
        }

        if(S->state != ST_GROUND) {
            GROUND_FLUSH();
            UTF8_FLUSH();
        }

        switch(S->state) {
            case ST_GROUND:
                if(first_ground < 0) {
                    first_ground = i;
                    ground_len = 1;
                } else {
                    ground_len++;
                }
                break;

            case ST_ESC:
                if(S->flags & MODE_VT52) {
                    S->state = ST_GROUND;
                    emu_ops_do_vt52_esc(S, ch);
                } else if(ch < 0x30) {
                    S->intermed = S->intermed ? 255 : ch;
                } else {
                    S->state = ST_GROUND;
                    emu_ops_do_esc(S, ch);
                }
                break;

            case ST_CSI:
                if(ch < 0x30) { // intermediate
                    S->intermed = S->intermed ? 255 : ch;
                } else if(ch < 0x3A) { // digit
                    S->paramVal = 10 * S->paramVal + (ch - 0x30);
                    CAP_MAX(S->paramVal, 16383);
                } else if(ch == 0x3A) { // colon (???)
                    // FIXME
                } else if(ch == 0x3B) { // semicolon
                    if(S->paramPtr < MAX_PARAMS)
                        S->params[S->paramPtr++] = S->paramVal;
                    S->paramVal = 0;
                } else if(ch < 0x40) { // private DEC stuff, treated as intermediate
                    S->intermed = S->intermed ? 255 : ch;
                } else { // dispatch
                    if(S->paramPtr < MAX_PARAMS)
                        S->params[S->paramPtr++] = S->paramVal;
                    emu_ops_do_csi(S, ch);
                    S->state = ST_GROUND;
                }
                break;

            case ST_OSC:
                // OSC is heavily underspecified in ECMA48. I've come up with
                // some rules here that mimic xterm's behavior.
                if(S->intermed == 0) {
                    if(ch >= 0x30 && ch < 0x3A) {
                        S->paramVal = 10 * S->paramVal + (ch - 0x30);
                    } else if(ch == 0x3b) {
                        S->intermed = 1;
                    } else {
                        S->state = ST_GROUND; // eh, whatever
                    }
                    break;
                }

                /*
                if(ch == 0x07 || ch == 0x9C || (ch == 0x5C && S->intermed == 2)) {
                    // ECMA48 specifies ST (ESC 0x5C or 0x9C), vt100 uses BEL.
                    // We allow both.
                    emu_ops_do_osc(S, S->paramVal);
                    S->state = ST_GROUND;
                }
                */

                if((ch >= 0x20 && ch < 0x7f) || (ch >= 0xa0)) {
                    // ECMA48 allows for "00/08 to 00/13 and 02/00 to 07/14",
                    // but I've tweaked the conditions a bit to allow UTF8 text
                    // and disallow control characters.
                    if((size_t)S->paramPtr < sizeof(S->oscBuf) - 1)
                        S->oscBuf[S->paramPtr++] = ch;
                } else {
                    // Invalid characters terminate OSC, so that you don't get
                    // stuck in OSC mode forever.
                    S->state = ST_GROUND;
                }
                break;
        }
    }

    GROUND_FLUSH();

    return len;

#undef GROUND_FLUSH
}
