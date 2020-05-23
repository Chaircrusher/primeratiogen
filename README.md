
**Usage: primeratiogen Scalename [PrimeCount] [SubsetSize]**

*Scalename* the name of the scale to embed in the Scala file.
*PrimeCount* the number of prime numbers starting with 2 to use
*SubsetSize* the number of notes to choose from the generated set of
ratios.

primeratiogen generates Scala tuning files according to a simple algorithm:

Take the first N primes, and make a set that permutes every
combination of prime ratios. Sort them ascending by numeric value.
Throw out any duplicates or fractions greater than 2 or less than 1
-- i.e. all that fit within a single octave.

Example:

The first 3 primes are 2, 3, and 5.

The permutations are
2/3, 3/2, 2/5, 5/2, 3/5, 5/3
In order by value:
2/5, 3/5, 2/3, 3/2, 5/3, 5/2

2/5 and 3/5 are less than one, and 5/2 is more than 2, so toss them.

You're left with 3 pitch ratios
3/2, 5/3, 2/1.

The *SubsetSize* argument says how many notes to include in the
scale. The notes chosen are the most evenly spaced subset of the
larger scale. This is done using the [Bjorklund
algorithm](https://gist.github.com/unohee/d4f32b3222b42de84a5f).

This is exactly how a Euclidean sequencer chooses note timing, but
instead of choosing the most equidistant events in the time domain,
the scale generator chooses the most equidistant N tones in an octave
of M tones.