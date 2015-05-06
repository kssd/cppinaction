#if !defined INPUT_H
#define INPUT_H
//------------------------------------
//  input.h
//  (c) Bartosz Milewski, 1994
//------------------------------------

const int maxBuf = 100;

// Tokens are tokNumber, tokError, +, -, *, /.

const int tokNumber = 1;
const int tokError  = 2;

// Gets input from stdin, converts to token.

class Input {
    public:
        Input ();
        int Token () const {
            return _token;
            }
        int Number () const;
    private:
        int  _token;
        char _buf [maxBuf];
    };

#endif // INPUT_H

