#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

// Sets the file to a constant char variable
//const char *fileName = "cipherShort.txt";

// Creates a struct to collect the orginal character and replacement character
struct cipherRule {
  char originalChar;
  char replacementChar;
};

/* Encryption function that takes the input text, the set of obtained rules from file, and the number of cipher rules. 
It loops trough the input and cipher rules, printing out the encrypted text*/
void encrypt(char input[], struct cipherRule rules[], int cipherSize) {
  printf("\nEncrypted text:\n");
  int c = 0;
  for(int i  = 0; i < strlen(input); i++) { 
  //while (input[c] != EOF) {
    for (int i = 0; i < cipherSize; i++) {
      if (toupper(input[c]) == rules[i].originalChar) {
        printf("%c", rules[i].replacementChar);
      }
    }
    c++;
  }
  printf("\n");
}

/* Decryption function that takes the input text, the set of obtained rules from file, and the number of cipher rules. 
It loops trough the input and cipher rules, printing out the unecrypted text */
void decrypt(char input[], struct cipherRule rules[], int cipherSize) {
  printf("\nDecrypted text:\n");
  int c = 0;

  for(int i  = 0; i < strlen(input); i++) { 
  //while (input[c] != EOF) {
    for (int i = 0; i < cipherSize; i++) {
      if (toupper(input[c]) == rules[i].replacementChar) {
        printf("%c", rules[i].originalChar);
      }
    }
    c++;
  }
  printf("\n");
}

int main(int argc, char *argv[]) {
 
  /*for(int i = 0; i < argc; i++) {
      printf("%c", argv[0]);
  }*/
  //printf("%c", argv[0]);


  bool errorTracker = false; // Boolean variable to track errors.
  bool cryptChoice; // Boolean variable to track whether the text is being encrypted and decrypted.

  char character;
  char encryptOrDecrypt[1];
  printf("\nEnter e for encrypt or d for decrypt: ");
  scanf("%s", encryptOrDecrypt); // Sets encryptOrDecrypted to value of input
  printf("You entered %s\n", encryptOrDecrypt);
  if (toupper(encryptOrDecrypt[0]) == 'E') {
    cryptChoice = true; // If e or E is entered then crypt choice is set to true
  } else if (toupper(encryptOrDecrypt[0]) == 'D') {
    cryptChoice = false; // If d or D is entered then crypt choice is set to true
  } else {
    errorTracker = true; // If any other character in entered, errorTracker is set to true and error is printed
    fprintf(stderr, "Wrong input choice. Rerun and input e, E, d, or D");
  }

  char inputText[100];
  if (!errorTracker) {
    printf("\nEnter string to be encrypted or decrypted: ");
    scanf("%s", inputText); // Sets entered text to inputText variable
    printf("You entered %s\n", inputText);
    /*FOR TESTING
    for (int i  = 0; i < strlen(inputText); i++) { 
      printf("%c", inputText[i]);
    }*/
  }

  FILE *fileLocation = fopen(argv[1], "r"); // Opens file of reading

  struct cipherRule addRule;
  struct cipherRule ruleArray[53];
  int cipherCounter = 0;

  while (!errorTracker) {
    char characterZero = toupper(fgetc(fileLocation));
    if (characterZero > 64 && characterZero < 123) { // Checks to see if 1st character is a letter (upper or lower)
      char tempComma = fgetc(fileLocation);
      if (tempComma == 44) { // Checks to see if 2nd character on the line is a comma
        char characterOne = toupper(fgetc(fileLocation));
        if (characterOne > 64 && characterZero < 123) { // Checks to see if 3rd character is a letter (upper or lower)
          addRule.originalChar = characterZero; // originalChar of addRule is set to the first character
          addRule.replacementChar = characterOne; // replacementChar of addRule is set to the first character
          ruleArray[cipherCounter] = addRule; // addRule is added to an struct cipherRule array
          cipherCounter++;
          /*FOR TESTING
          printf("%c --> %c\n", addRule.originalChar, addRule.replacementChar);*/
        } else { // Error is printed, errorTracker is set to true, and while loop is broken
          fprintf(stderr, "Format of text file is wrong");
          errorTracker = true;
          break;
        }
      } else { // Error is printed, errorTracker is set to true, and while loop is broken
        fprintf(stderr, "Format of text file is wrong");
        errorTracker = true;
        break;
      }
    } else { // Error is printed, errorTracker is set to true, and while loop is broken
      fprintf(stderr, "Format of text file is wrong");
      errorTracker = true;
      break;
    }
    char checkEndCharacter = fgetc(fileLocation); 
    if (checkEndCharacter == EOF) { // At the end of each line, the character is checked to be EOF and if it is EOF the loop will be broken
      break;
    }
  }

  /* If errorTracker is set to false, the conditional statements check to see if there are any duplicates in the rules
  If there any duplicates, errorTracker is set to true, the foor loops are broken, and an error message printed. */
  if (!errorTracker) {
    for (int a = 0; a < cipherCounter - 1; a++) {
      for (int b = a + 1; b < cipherCounter; b++) {
        if (ruleArray[a].originalChar == ruleArray[b].originalChar) {
          fprintf(stderr, "\nDuplicate rules found. Edit file to remove duplicates in the left side and rerun.");
          errorTracker = true;
          break;
        }
        if (ruleArray[a].replacementChar == ruleArray[b].replacementChar) {
          fprintf(stderr, "\nDuplicate rules found. Edit file to remove duplicates in the right side and and rerun.");
          errorTracker = true;
          break;
        }
      }
    }
  }
     
  /*for(int i = 0; i < cipherCounter; i++) {
        printf("%c --> %c\n", ruleArray[i].originalChar, ruleArray[i].replacementChar);
    }*/
  // If errorTracker is set to false and depending of the value of the boolean variable, the encryption or decryption functions are run with the assoicated.
  if (!errorTracker) {
    if (cryptChoice) {
      encrypt(inputText, ruleArray, cipherCounter);
    } else {
      decrypt(inputText, ruleArray, cipherCounter);
    }
  }

  fclose(fileLocation);
  return (0);
}