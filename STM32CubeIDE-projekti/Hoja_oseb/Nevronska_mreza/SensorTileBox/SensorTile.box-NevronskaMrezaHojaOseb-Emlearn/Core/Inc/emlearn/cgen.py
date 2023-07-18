
"""Utilities to generate C code"""


import re

VALID_IDENTIFIER_REGEX = r'^[_a-zA-Z][_a-zA-Z0-9]*$' # valid C identifiers
from .creserved import RESERVED_WORDS

def struct_init(*args):
    """Struct initializer

    >>> from emlearn import cgen
    >>> cgen.struct_init([ 1, 2, 3 ])
    "{ 1, 2, 3 }"
    """

    return '{ ' + ', '.join(str(a) for a in args) + ' }'


def constant(val, dtype='float'):
    """A literal value

    >>> from emlearn import cgen
    >>> cgen.constant(3.14)
    "3.14f"
    """
    if dtype == 'float':
        return "{:.6f}f".format(val)
    else:
        return str(val)

def constant_declare(name, val, dtype='int'):
    v = constant(val, dtype=dtype)
    return f'static const {dtype} {name} = {v}; '

def array_declare(name, size=None, dtype='float', modifiers='static const',
                    values=None, end='', indent=''):

    """
    Declare and optionally initialize an array.


    >>> from emlearn import cgen
    >>> cgen.array_declare("declareonly", 10)
    "static const float declareonly[10];"

    Also intialize it.

    >>> from emlearn import cgen
    >>> cgen.array_declare("initialized", 3, dtype='int', modifiers='const')
    "const int initialized[3] = { 1, 2, 3 };"
    """
    if values is not None:
        if size is None:
            size = len(values)
        assert size == len(values), 'size does not match length'

    init = ''
    if values is not None:
        init_values = ', '.join(constant(v, dtype) for v in values)
        init = ' = {{ {init_values} }}'.format(**locals())

    return '{indent}{modifiers} {dtype} {name}[{size}]{init};{end}'.format(**locals())

def identifier_is_valid(s):
    match = re.match(VALID_IDENTIFIER_REGEX, s)
    return match is not None

def identifier_is_reserved(s):
    reserved = s in RESERVED_WORDS
    return reserved

def assert_valid_identifier(s):

    valid = identifier_is_valid(s)
    if not valid:
        raise ValueError(f"'{s}' is not a valid C identifier")
        
    reserved = identifier_is_reserved(s)
    if reserved:
        raise ValueError(f"'{s}' is a reserved word in C")

