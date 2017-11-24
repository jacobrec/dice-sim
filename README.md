# dice-sim
a parser for a dice rolling language

Uses a recursive descent parser to construct an abstract syntax tree, then evaluates it to determine probabilities,

## Usage
Some example statements(these are all the same)
    4d6
    2d6 + 2d6
    (2*2)d(2*3)
Use differnt flags while running for differnt outputs
    ./dice -n `#This is to supress frequencey output`
    ./dice -p `#This is to show the abstract syntax tree in ascii art`
    ./dice -l `#This is to show the token stream`
