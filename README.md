# dict
Simple associative array single-header library

This is single header file library for associative arrays, either
associating an `int64_t` value with another `int64_t` value or a string
with another string. For the numeric associative array, the type
and function prefix is `dict`. For the string associative array, the
type and function prefix is `sdict`. 

## Usage:

Some users may find that defining a macro for the value function makes
usage a bit more ergonomic. The library does not provide these due to
namespace issues, user-programmers' individual preferences, and 
varied compiler support for the author's preferred macro names.

```c
#include <stdio.h>
#include "dict.h"

int main(void) {
    dict *cpgmap = dictnew();
    sdict *uamap = sdictnew();
    #define cpgmap_(x) dictval(cpgmap, x)
    #define uamap_(x) sdictval(uamap, x)
    
    dictadd(cpgmap, 0, 1252);
    dictadd(cpgmap, 178, 1256);
    // ...
    sdictadd(uamap, "Win/FFX 83", "Mozilla/5.0 (Windows NT 10.0; "\
                    "Win64; x64; rv:83.0) Gecko/20100101 Firefox/83.0");
    sdictadd(uamap, "Mac/Safari 12", "Mozilla/5.0 (Macintosh; Intel"\
                    "Mac OS X 10_15_5 (Ergänzendes Update)) "\
                    "AppleWebKit/605.1.15 (KHTML, like Gecko) "\
                    "Version/12.1.1 Safari/605.1.15");
    // ...

    int64_t codepage = cpgmap_(178);
    printf("Charset 178 => code page %lld\n", codepage);
    
    char *activeua = uamap_("Win/FFX 83");
    printf("The full user agent for Win/FFX 83 is \'%s\'\n", activeua);

    free(activeua);
    dictdestroy(cpgmap);
    sdictdestroy(uamap);

    return 0;
}
```

The associative array is implemented as a sorted array of 
key-value structures. Value retrieval and value insertion are both
implemented via binary search for the anticipated location of the
given key. On insertion, if the key exists, the existing value is
overwritten; if it does not, the elements after that point, if
any, are shifted to the right and a new key-value pair is inserted.
While this approach is O(log n) rather than O(1), the performance
characteristics for most situations are acceptable.