#include <iostream>
#include <sstream>
#include <assert.h>
#include <string>

using namespace std;

class MoveNotRecognized {
public:
  MoveNotRecognized( char c ): move(c) { }

  string message( void ) const {
    return string( "Santa does not recognized '" ) + move + "' move.";
  }

private:
  char move;
};

class CSanta {
public:
  static int whereIAm( istream & is, const bool basement = false ) {
    char input = 'x';
    int  floor = 0;
    int  step = 0;

    while( is >> input ) {
      step++;

      if( '(' == input ) floor++;
      else if( ')' == input ) floor--;
      else throw MoveNotRecognized( input );

      if( -1 == floor && true == basement ) return step;
    }

    return floor;
  }

  static int whenAtBasement( istream & is ) {
    return CSanta::whereIAm( is, true );
  }
};

void testsP1( void ) {
  istringstream iss;

  iss.str( "" );
  iss.clear();
  iss.str( "(())" );
  assert( 0 == CSanta::whereIAm( iss ) );

  iss.str( "" );
  iss.clear();
  iss.str( ")())())" );
  assert( 3 == CSanta::whereIAm( iss ) );

  iss.str( "" );
  iss.clear();
  iss.str( "p())" );
  try {
    CSanta::whereIAm( iss );
    assert( 1 == 0 );
  } catch ( MoveNotRecognized m ) { }
}

void testsP2( void ) {
  istringstream iss;

  iss.str( "" );
  iss.clear();
  iss.str( ")" );
  assert( 1 == CSanta::whenAtBasement( iss ) );

  iss.str( "" );
  iss.clear();
  iss.str( "()())" );
  assert( 5 == CSanta::whenAtBasement( iss ) );
}

void runP1( void ) {
  try {
    int floor = CSanta::whereIAm( cin );

    cout << floor << endl;
  } catch ( MoveNotRecognized m ) {
    cout << m.message() << endl;
  }
}

void runP2( void ) {
  try {
    int step = CSanta::whenAtBasement( cin );

    cout << step << endl;
  } catch ( MoveNotRecognized m ) {
    cout << m.message() << endl;
  }
}

int main( void ) {
  runP2();
  return 0;
}
