#include <stdio.h>
#include <time.h>
#include "dict.h" 

static const char *words[75] = { "attack", "attention", "attorney", "audience", 
"author", "authority", "available", "avoid", "away", "behavior", "behind", 
"believe", "benefit", "best", "better", "between", "consider", "consumer", 
"contain", "continue", "control", "cost", "could", "country", "difficult", 
"dinner", "direction", "everybody", "everyone", "everything", "evidence", 
"exactly", "example", "increase", "indeed", "indicate", "individual", 
"industry", "measure", "media", "medical", "meet", "name", "nation", 
"national", "natural", "nature", "president", "pressure", "pretty", "prevent", 
"price", "private", "probably", "problem", "respond", "response", 
"responsibility", "rest", "result", "successful", "such", "suddenly", 
"suffer", "suggest", "summer", "support", "thousand", "threat", "three", 
"through", "western", "woman", "young", "yourself" };

int main(void) {
    dict *D = dictnew();
    sdict *S = sdictnew();
    size_t i;
    int64_t tgt;
    char tgts[64];

    srand((unsigned int)time(NULL));

    // Fill up the dictionaries
    for (i = 0; i < 20; i++) {
        tgt = 1000 + (99-(int64_t)i);
        snprintf(tgts, 64, "%lld", tgt);
        dictadd(D, tgt, rand());
        sdictadd(S, tgts, words[rand() % 75]);
    }

    // Print out the number dictionary
    for (i = 0; i < 20; i++) {
        tgt = 1000+(99-(int64_t)i);
        snprintf(tgts, 64, "%lld", tgt);
        printf("%lld is mapped to %lld\t\t", tgt, dictval(D, tgt));
        printf("\"%s\" is mapped to \"%s\"\n", tgts, sdictval(S, tgts));
    }
    
    dictdestroy(D);
    sdictdestroy(S);

    return 0;
}
