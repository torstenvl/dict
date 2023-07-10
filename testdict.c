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
    size_t i;
    dict *D = dictnew();

    srand((unsigned int)time(NULL));
    for (i = 0; i < 20; i++) {
        D->add(D, words[rand() % 75], words[rand() % 75]);
    }

    dictprint(D);
    
    dictdestroy(D);

    return 0;
}
