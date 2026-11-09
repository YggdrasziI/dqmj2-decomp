# Matching techniques

Compiler idioms and source forms that fix near-misses in this ROM, each with the
function it worked on and the compiler (2.0/sp2p2 unless stated otherwise).

## Branches and stores

- A global address loaded in both arms of a conditional (`cmp r0, #0; ldrlt r1, =g;
  rsblt r0, r0, #0; ldrge r1, =g; str r0, [r1, #x]`) comes from a store written in
  each branch, `if (v < 0) g.f = -v; else g.f = v;`; `if (v < 0) v = -v; g.f = v;`
  loads the address once before the `cmp` (57 % -> 100 %, `func_02040c98`,
  `func_02040cb4`).

## Registers

- A repeated subexpression written out instead of kept in a local: in
  `func_02040cd0` the original loads `fade->target` into r1 and sets the division
  arguments `r0 = 16` before `r1 = range`; with a local `range = 16 - fade->target`
  the load goes to r0 and the arguments are set in the other order (99.75 %).
  Writing `(16 / (16 - fade->target)) * ((fade->frame * (16 - fade->target)) /
  fade->duration)` gives 100 %. Declaration order of the locals also moved this
  function from 98.66 % to 99.75 % (`target, level, done, dir, finished`; found by
  a script over the permutations).

Beyond these, read the sibling project's notes,
`E:\Projets\Dev\ts2-castaway\notes\MATCHING.md` (mwccarm 2.0, ARM code). A technique
from there is recorded here only once it has worked on a function of this ROM, with
the function and the compiler it was tried with: this game may use another compiler,
other flags and much more Thumb code.
