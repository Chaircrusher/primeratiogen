// primeratiogen: by Kent Williams chaircrusher@gmail.com
// generates just intonation scales, i.e. every note is a ratio of two
// prime numbers.
// The constraint to primes was my idea; you could as easily just use
// any other list of numbers including 2,3,4,5 etc.
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include "Bjorklund.h"

// list of primes
double primes[] = {
  2.0,  3.0,  5.0,  7.0, 11.0, 13.0,
  17.0, 19.0, 23.0, 29.0, 31.0, 37.0,
  41.0, 43.0, 47.0, 53.0, 59.0, 61.0,
  67.0, 71.0, 73.0, 79.0, 83.0, 89.0,
  97.0, 101.0, 103.0, 107.0, 109.0, 113.0,
  127.0, 131.0, 137.0, 139.0, 149.0, 151.0,
  157.0, 163.0, 167.0, 173.0, 179.0, 181.0,
  191.0, 193.0, 197.0, 199.0
};
const int numPrimes=sizeof(primes)/sizeof(double);

// rational number
class rational {
public:
  // constructor
  rational(double a, double b) : m_Numerator(a), m_Denominator(b) {}
  // value of ratio
  double val() const { return m_Numerator/m_Denominator; }
  // numerator
  double num() { return m_Numerator; }
  // denominator
  double denom() { return m_Denominator; }
  // assignment
  rational &operator=(const rational &other) {
    this->m_Numerator = other.m_Numerator;
    this->m_Denominator = other.m_Denominator;
    return *this;
  }
  // equality
  bool operator==(const rational &b) {
    return this->m_Numerator == b.m_Numerator && this->m_Denominator == b.m_Denominator;
  }
private:
  // values
  double m_Numerator, m_Denominator;
};

// vector of rational
typedef std::vector<rational> rationalVec;
// iterator for vector of rational
typedef rationalVec::iterator rationalIt;
// compare two rationals
bool ratioCompare(const rational &a, const rational &b) {
  return a.val() < b.val();
}
// check for membership of value in rational vector
bool alreadyIn(rationalVec &vec, rational &val) {
  return std::find(vec.begin(), vec.end(), val) != vec.end();
}

int main(int argc, char **argv) {
  if(argc < 2) {
    std::cerr << argv[0];
    std::cerr << ": Usage: primeratiogen Scalename [PrimeCount]";
    std::cerr << "missing scale name";
    std::cerr << std::endl;
    return 1;
  }
  const char *scaleName = argv[1];
  // if no primecount given use all primes given above
  unsigned int primeCount(numPrimes);
  if(argc > 2)
    primeCount = atoi(argv[2]);
  int subset(-1);
  if(argc > 3)
    subset = atoi(argv[3]);
  // sanity check on prime count
  if(primeCount <= 0 || primeCount > numPrimes)
    primeCount = numPrimes;
  // vector to hold rational numbers
  rationalVec v;
  // permute throuth the first 'primeCount' primes, record the ratios
  for(unsigned i=0; i < primeCount; ++i) {
    for(unsigned j=0; j < primeCount; ++j) {
      rational cur(primes[i],primes[j]);
      if(j == i ||			  // don't include 1/1
	 cur.val() < 1.0 ||  // don't include numbers < 1
	 cur.val() >= 2.0 || // don't include numbers > 2
	 alreadyIn(v,cur))	  // don't include the same value twice
	// (shouldn't ever happen)
	continue;
      v.push_back(cur);		  // add to list
    }
  }
  std::sort(v.begin(), v.end(), ratioCompare); // sort the list ascending
  // put out scala header
  std::cout << "! " << scaleName << std::endl
	    << "!" << std::endl;
  // scale name
  std::cout << scaleName << std::endl;

  // if subset is larger than list of generated ratio, set it to that.
  if(subset >= v.size())
    subset = v.size();

  // size of scale
  std::cout << " ";
  if(subset < 0) {
    std::cout << (v.size()+1);
  } else {
    std::cout << subset + 1;
  }
  std::cout << std::endl;
  std::cout << "!" << std::endl;
  // no subset requested, print all
  if(subset < 0) {
    for(rationalIt it = v.begin(); it != v.end(); ++it) {
      std::cout << it->num() << "/" << it->denom() << std::endl;
    }
  } else {
    Bjorklund b(v.size(), subset);
    std::vector<bool> bv = b.LoadSequence();
    rationalIt it = v.begin();
    for(unsigned i = 0;
	it != v.end() && i < bv.size();
	++i, ++it) {
      if(bv[i])
	std::cout << it->num() << "/" << it->denom() << std::endl;
    }
  }
  // cap with last note
  std::cout << "2/1" << std::endl;
  return 0;
}
