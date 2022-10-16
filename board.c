#include "board.h"

int legal(const NCBoard *position, int move) {
    if (move < 0 || move > 8) return 0;
    if ((position->noughts >> move) & 1) return 0;
    if ((position->crosses >> move) & 1) return 0;
    return 1;
}

void play(NCBoard *position, int move) {
    switch (position->side) {
        case NOUGHTS:
            position->noughts += (1 << move);
            break;
        case CROSSES:
            position->crosses += (1 << move);
            break;
    }
    position->side = position->side ^ 1;
    position->movelist[position->nbmoves] = move;
    ++position->nbmoves;
}

void playseq(NCBoard *position, char* seq) {
    int seqlen = 0;
    for (int c = 0; seq[c] != '\0'; ++c) ++seqlen;
    for (int i = 0; i < seqlen; ++i) {
        play(position, seq[i] - '0');
    }
}

void unmake(NCBoard *position) {
    --position->nbmoves;
    int move = position->movelist[position->nbmoves];
    position->side = position->side ^ 1;
    switch (position->side) {
        case NOUGHTS:
            position->noughts -= (1 << move);
            break;
        case CROSSES:
            position->crosses -= (1 << move);
            break;
    }
}

int alignment(unsigned short position) {
    if (position & (position >> 1) & (position >> 2)) return 1;
    if (position & (position >> 3) & (position >> 6)) return 1;
    if (position & (position >> 4) & (position >> 8)) return 1;
    if (position & (position >> 2) & (position >> 4)) return 1;
    return 0;
}

void display(const NCBoard *position) {
    printf("\n ");
    for (int i = 0; i < 9; ++i) {
        if (i) {
            i % 3 == 0 ? printf("\n-----------\n ") : printf(" | ");
        }

        if ((position->noughts >> i) & 1) {
            printf("%c", NOUGHTS_CHAR);
        } else if ((position->crosses >> i) & 1) {
            printf("%c", CROSSES_CHAR);
        } else {
            printf(" ");
        }
    }
    printf("\n\n");
}

int main() {
    NCBoard position;
    position.side = NOUGHTS;
    position.noughts = 0;
    position.crosses = 0;

    display(&position);
    playseq(&position, "012345678");
    display(&position);

    return 0;
}