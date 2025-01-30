#include <iostream>
using namespace std;

/**
 * Defines a class named Complex to represent complex numbers. Performs mathematical
 * operations via member functions. Overloads the operators <<, >>, +, -, *, /, ==, !=.
 * Takes user input and tests their functionality in the main function.
 * @author     Jasmine Quach
 * @assignment ICS 212 Assignment 20
 * @date       December 5, 2024
 */

/** Complex class definition (abstract data type (ADT)) */
class Complex {

public:

  /** constructs a Complex object */                                                                
  Complex() {
    real = 0.0;
    imaginary = 0.0;
  }

  /**
   * constructs a Complex object + assigns real and imaginary parts
   * @param realParam        the real number
   * @param imaginaryParam   the imaginary number 
   */
  Complex(double realParam, double imaginaryParam) {
    real = realParam;
    imaginary = imaginaryParam;
  }

  /**
   * copy constructor makes a copy of a complex number
   * @param copyComplex   Complex object to be copied
   */
  Complex(const Complex &copyComplex) {
    set(copyComplex.real, copyComplex.imaginary);   // set function assigns values
    cout << "Copy constructor called.\n";
  }

  /** destructor for deleting object */
  ~Complex() {
    cout << "Destructor for: (";
    // operator depends on whether imaginary part is + or -  
    if (imaginary >= 0) {
      cout << real << " + " << imaginary << "i)\n";
    } else {
      cout << real << " - " << -imaginary << "i)\n";
    }
  }

  /** prints a complex number in the format (a + bi) */
  void print() const {
    cout << "(" << real;
    // operator depends on whether imaginary part is + or -
    if (imaginary >= 0) {
      cout << " + " << imaginary << "i)\n";
    } else {
      cout << " - " << -imaginary << "i)\n";  // "-imaginary" turns "- -" into "+"
    }
  }

  /**
   * assigns the real and imaginary data members respectively
   * @param newReal        the real number
   * @param newImaginary   the imaginary number
   */
  void set(double newReal, double newImaginary) {
    real = newReal;
    imaginary = newImaginary;
  }

  /** accessor methods */
  double getReal() const {
    return real;
  }
  double getImaginary() const {
    return imaginary;
  }

  /**
   * ADDS the current Complex number to another
   * @param addComplex   the Complex object to be added to the current object
   * @return a new Complex object that represents the sum of the two complex numbers  
   */
  Complex add(const Complex &addComplex) const {
    // follows formula (a + bi) + (c + di) = (a + c) + (b + d)i
    double newReal = real + addComplex.real;
    double newImaginary = imaginary + addComplex.imaginary;

    // return a new object with above sums as parameters
    return Complex(newReal, newImaginary);
  }

  /**
   * SUBTRACTS another Complex object from the current one
   * @param subtractComplex   the Complex object to be subtracted from the current object
   * @return a new Complex object that represents the difference of the two complex numbers
   */
  Complex subtract(const Complex &subtractComplex) const {
    // follows formula (a + bi) - (c + di) = (a - c) + (b - d)i
    double newReal = real - subtractComplex.real;
    double newImaginary = imaginary - subtractComplex.imaginary;

    // return a new object with above differences as parameters
    return Complex(newReal, newImaginary);
  }

  /**
   * MULTIPLIES the current Complex object by another
   * @param multiplyComplex   the Complex object to multiply with the current object
   * @return a new Complex object that represents the product of the two complex numbers
   */
  Complex multiply(const Complex &multiplyComplex) const {
    // follows formula (a + bi) * (c + di) = (a*c - b*d) + (b*c + a*d)i
    double newReal = real * multiplyComplex.real - imaginary * multiplyComplex.imaginary;
    double newImaginary = imaginary * multiplyComplex.real + real * multiplyComplex.imaginary;

    // return a new object with above products as parameters
    return Complex(newReal, newImaginary);
  }

  /**
   * DIVIDES the current Complex object by another
   * @param divideComplex   the Complex object to be divided by the current object
   * @return a new Complex object that represents the quotient of the two complex numbers
   */
  Complex divide(const Complex &divideComplex) const {
    // follows formula (a + bi) / (c + di) = ((a*c + b*d)/(c*c + d*d)) + ((b*c - a*d)/(c*c + d*d))i
    double newReal = (real * divideComplex.real + imaginary * divideComplex.imaginary) / (divideComplex.real * divideComplex.real + divideComplex.imaginary * divideComplex.imaginary);
    double newImaginary = (imaginary * divideComplex.real - real * divideComplex.imaginary) / (divideComplex.real * divideComplex.real + divideComplex.imaginary * divideComplex.imaginary);

    // return a new object with above quotients as parameters
    return Complex(newReal, newImaginary);
  }

  /**
   * Overload the >> to create Complex objects with cin >>.
   * User should type in the format: integer, followed by another integer, followed by an i
   *   a+bi
   *   a-bi
   * Where a and b are integers.
   * For simplicity, this overloaded >> only reads in integer real and integer imaginary parts.
   * The data members of the Complex class still use the double data type. No change to
   * any existing data types for data members are made.
   *
   * This function does not enforce the i to be an i.
   *
   *
   * @param in The input stream where data is being retrieved.
   * @param complexIn The Complex object that is set based on the input.
   * @return The cleared input stream. The Complex object complexIn was set.
   */
  friend istream &operator>>(istream &in, Complex &complexIn) {
    // Used to store the letter 'i' from the input.
    char letter_i = 'i';

    // Stores the real and imaginary parts entered by the user.
    // Although these are int variables, the actual data members
    // of Complex should still be double.
    int tempReal = 0;
    int tempImaginary = 0;

    // Read input a+bi and store the real and imaginary parts.
    in >> tempReal >> tempImaginary >> letter_i;
 
    // Assign the real and imaginary input to the Complex object
    complexIn.set(tempReal, tempImaginary);
       
    // Clear the input stream.
    in.clear();
    return in;
  }

  /**
   * overloads the << operator to display Complex objects with cout << in (a+bi) format
   * @param out            the output stream where the Complex object is displayed
   * @param complexParam   the Complex object to be displayed on the output stream
   * @return the output stream
   */
  friend ostream &operator<<(ostream &out, const Complex &complexParam) {
    out << "(" << complexParam.real;
    // check if imaginary part is positive or negative
    if (complexParam.imaginary >= 0) {
      out << "+" << complexParam.imaginary << "i)";
    } else {
      // if negative, automatically has a - sign
      out << complexParam.imaginary << "i)";
    }
    return out;
  }

  /**
   * overloads the + operator to add two Complex objects inputted by the user
   * @param complexLeft    the left Complex object to be added
   * @param complexRight   the right Complex object to be added
   * @return a new Complex object that represents the sum of the two complex numbers
   */
  friend Complex operator+(const Complex &complexLeft, const Complex &complexRight) {
    // add the objects using formula (a + bi) + (c + di) = (a + c) + (b + d)i
    double newReal = complexLeft.real + complexRight.real;
    double newImaginary = complexLeft.imaginary + complexRight.imaginary;

    // return a new object with the above sums as parameters
    return Complex(newReal, newImaginary);
  }

  /**
   * overloads the - operator to subtract Complex objects inputted by the user
   * @param subtractComplex    the Complex object to be subtracted from the current one
   * @return a new Complex object that represents the difference of the two complex numbers
   */
  Complex operator-(const Complex &subtractComplex) const {
    // subtract the objects using formula (a + bi) - (c + di) = (a - c) + (b - d)i
    double newReal = real - subtractComplex.real;
    double newImaginary = imaginary - subtractComplex.imaginary;

    // return a new object with the above differences as parameters
    return Complex(newReal, newImaginary);
  }

  /**
   * overloads the * operator to multiply Complex objects inputted by the user
   * @param multiplyComplex    the Complex object to be multiplied by the current one
   * @return a new Complex object that represents the product of the two complex numbers
   */
  Complex operator*(const Complex &multiplyComplex) const {
    // multiply the objects using formula (a + bi) * (c + di) = (a*c - b*d) + (b*c + a*d)i
    double newReal = real * multiplyComplex.real - imaginary * multiplyComplex.imaginary;
    double newImaginary = imaginary * multiplyComplex.real + real * multiplyComplex.imaginary;

    // return a new object with the above products as parameters
    return Complex(newReal, newImaginary);
  }

  /**
   * overloads the / operator to divide Complex objects inputted by the user
   * @param divideComplex    the Complex object to be divided by the current one
   * @return a new Complex object that represents the quotient of the two complex numbers
   */
  Complex operator/(const Complex &divideComplex) const {
    // divides the objects using formula (a + bi) / (c + di) = ((a*c + b*d)/(c*c + d*d)) + ((b*c - a*d)/(c*c + d*d))i
    double newReal = (real * divideComplex.real + imaginary * divideComplex.imaginary) / (divideComplex.real * divideComplex.real + divideComplex.imaginary * divideComplex.imaginary);
    double newImaginary = (imaginary * divideComplex.real - real * divideComplex.imaginary) / (divideComplex.real * divideComplex.real + divideComplex.imaginary * divideComplex.imaginary);

    // return a new object with the above quotients as paramaters
    return Complex(newReal, newImaginary);
  }

  /**
   * overloads the == operator to compare two Complex objects
   * @param complexLeft     the left Complex object to be compared
   * @param complexRight    the right Complex object to be compared
   * @return true if the Complex objects are the same, false otherwise 
   */
  friend bool operator==(const Complex &complexLeft, const Complex &complexRight) {
    // compare the real and imaginary parts of both numbers ... only true if both parts are equal to their counterparts
    return (complexLeft.real == complexRight.real) && (complexLeft.imaginary == complexRight.imaginary);
  }

  /**
   * overloads the != operator to compare two Complex objects
   * @param complexLeft     the left Complex object to be compared                                                                                                                                 
   * @param complexRight    the right Complex object to be compared                                                                                                                                
   * @return true if the Complex objects are the NOT same, false otherwise
   */
  friend bool operator!=(const Complex &complexLeft, const Complex &complexRight) {
    // compare the complex numbers ... true if they are not equal
    return !(complexLeft == complexRight);
  }

  // data members at bottom by convention
private:
  double real;
  double imaginary;

};


// test Complex class in main function
int main(void) {

  // Used to store the two Complex objects from user input.
  Complex complex1;
  Complex complex2;
  // A blank Complex object used to store the results of the Complex arithmetic.
  Complex complex3;

  // Get 2 Complex objects from the user.
  cout << "Enter a Complex number in the form 'a+bi': ";
  cin >> complex1;
  cout << "Enter another Complex number in the form 'a+bi': ";
  cin >> complex2;
  
  cout << endl;
  
  // Test the + overloaded operator.
  cout << "Test the + operator:" << endl;
  complex3 = complex1 + complex2;
  cout << complex1 << " + " << complex2 << " = " << complex3 << endl;

  cout << "\n";
  
  // Test the - overloaded operator.
  cout << "Test the - operator:" << endl;
  complex3 = complex1 - complex2;
  cout << complex1 << " - " << complex2 << " = " << complex3 << endl;

  cout << "\n";
  
  // Test the * overloaded operator.
  cout << "Test the * operator:" << endl;
  complex3 = complex1 * complex2;
  cout << complex1 << " * " << complex2 << " = " << complex3 << endl;

  cout << "\n";

  // Test the / overloaded operator.
  cout << "Test the / operator:" << endl;
  complex3 = complex1 / complex2;
  cout << complex1 << " / " << complex2 << " = " << complex3 << endl;

  cout << "\n";
  
  // Test the == overloaded operator.
  cout << "Test the == operator:" << endl;
  // Turn on boolalpha to actually print true or false instead of 1 or 0.
  cout << complex1 << " == " << complex2 << " = " << boolalpha << (complex1 == complex2) << endl;

  cout << "\n";
  
  // Test the != overloaded operator.
  cout << "Test the != operator:" << endl;
  cout << complex1 << " != " << complex2 << " = " << (complex1 != complex2) << endl;

  cout << "\n";

  return 0;

}
