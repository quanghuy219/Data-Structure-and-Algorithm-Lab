#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

int main(){
  char article[5][10] = {"the", "a", "one", "some", "any"};
  char noun[5][10] = {"boy", "girl", "dog", "town", "car"};
  char verb[5][10] = {"drove", "jumped", "ran", "walked", "skipped"};
  char preposition[5][10] = {"to", "from", "over", "under", "on"};
  char sentence[10][50];
  int i, num_article1, num_subject, num_verb, num_preposition,num_article2, num_object;

  srand(time(NULL));
  for (i = 0; i < 10; i++) {
    
    num_article1 = rand() % 5;
       
    num_subject = rand() % 5;
    

    num_verb = rand() % 5;

    num_preposition = rand() % 5;

    num_article2 = rand() % 5;

    num_object = rand() % 5;

    if (num_article1 == 3) {
      sprintf(sentence[i], "%s %ss %s %s %s %s.", article[num_article1], noun[num_subject], verb[num_verb], preposition[num_preposition], article[num_article2], noun[num_object]);

	 if (num_article2 == 3) {
      sprintf(sentence[i], "%s %ss %s %s %s %ss.", article[num_article1], noun[num_subject], verb[num_verb], preposition[num_preposition], article[num_article2], noun[num_object]);	 
	 }
    }

   else if (num_article2 == 3) {
      sprintf(sentence[i], "%s %s %s %s %s %ss.", article[num_article1], noun[num_subject], verb[num_verb], preposition[num_preposition], article[num_article2], noun[num_object]);
    }
    
   else {
      sprintf(sentence[i], "%s %s %s %s %s %s.", article[num_article1], noun[num_subject], verb[num_verb], preposition[num_preposition], article[num_article2], noun[num_object]);
    }
    
    sentence[i][0] = toupper(sentence[i][0]);

    printf("%s\n",sentence[i]);
  }
  return 0;
}
