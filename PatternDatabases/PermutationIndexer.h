#ifndef RUBIKS_CUBE_SOLVER_PERMUTATIONINDEXER_H
#define RUBIKS_CUBE_SOLVER_PERMUTATIONINDEXER_H



#include "math.h"
#include "bits/stdc++.h"
using  namespace std;

template<size_t N, size_t K = N>
class PermutationIndexer{
    //precomputed table containing the number of one in the binary
    // representation of each number. the largest N-bit number is
    //2^N-1 = (1<<N) - 1.
    array<uint32_t , (1<<N)-1> onesCountLookup;


    //precomputed table of factorials (or "picks" if N != K). They're in
    // reverse order
    arr<uint32_t, K> factorials;

    public:
        /*
         * populate factorials and ones-count tables
        */
          PermutationIndexer(){

            for(uint32_t i=0; i< (1<<N)-1; i++){
                bitset<N> bits(i);
                this->onesCountLookup[i] = bits.count();
            }
            for(uint32_t i=0; i<K; i++){
                this->factorials[i] = pick(N-1-i , K-1-i);
            }

          }

          /*
           * Calculate the lexicographic rank(the index) of a permutation in O(n)
           * complexity
           */

          uint32_t rank(const array<uint8_t, K>&perm) const
          {
            //This will hold the lehmer code (in a factorial sysytem)
                array<uint32_t,K> lehmer;

            //set of "seen" digits in the permutation
            bitset<N> seen;

            //The first digit of lehmer code is always the first digit of permutation
            lehmer[0] = perm[0];

            //Mark the digit as seen (bitset uses right-left-indexing)
            seen[N-1-perm[0]] = 1;

            for(uint32_t i=1; i<K; i++){
                seen[N-1-perm[i]]=1;
                //The number of "seen" digits to the left of this digit is the
                //count of ones left of this digit

                uint32_t numOnes = this->onesCountLookup[seen.to_ulong() >> (N-perm[i])];

                leher[i] = perm[i] - numOnes
            }
            //convert the lehmer code to base-10
            uint32_t index = 0;

            for(uint32_t i=0; i<K; i++){
                index += lehmer[i] * this->factorials[i];
            }
            return index;

          }
};

#endif //RUBIKS_CUBE_SOLVER_PERMUTATIONINDEXER_H

