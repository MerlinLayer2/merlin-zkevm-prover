#include "keccak.hpp"

void KeccakF (KeccakState &S)
{
    // Rnd(A, ir) = ι( χ( π( ρ( θ(A) ) ) ), ir)
    for (uint64_t ir=0; ir<24; ir++ )
    {
        //if (ir==0) S.printRefs(S.SinRefs, "Before theta");
        KeccakTheta(S, ir);
        S.copySoutRefsToSinRefs();
        //if (ir==0) S.printRefs(S.SinRefs, "After theta");
        KeccakRho(S);
        S.copySoutRefsToSinRefs();
        //if (ir==0) S.printRefs(S.SinRefs, "After rho");
        KeccakPi(S);
        S.copySoutRefsToSinRefs();
        //if (ir==0) S.printRefs(S.SinRefs, "After pi");
        KeccakChi(S);
        S.copySoutRefsToSinRefs();
        //if (ir==0) S.printRefs(S.SinRefs, "After chi");
        KeccakIota(S, ir);
        if (ir!=23) S.copySoutRefsToSinRefs();
        //if (ir==0) S.printRefs(S.SinRefs, "After iota");
    }

    // Add 1600 more gates to make sure that Sout is located in the expected gates,
    // both in pin a and r
    for (uint64_t i=0; i<1600; i++)
    {
        uint64_t aux;
        aux = SoutRef0 + 9*i;
        S.XOR( S.SoutRefs[i], pin_r, ZeroRef, pin_a, aux );
        S.SoutRefs[i] = aux;
        //cout << "KeccakF() i=" << i << " aux=" << aux << " pin_a=" << (uint64_t)S.gate[S.SoutRefs[i]].pin[pin_a].bit << " pin_r=" << (uint64_t)S.gate[S.SoutRefs[i]].pin[pin_r].bit << endl;
    }
}