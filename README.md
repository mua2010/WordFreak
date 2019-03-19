# WordFreak

                                  Word Freak 

We are creating a linked list of words(along with their frequencies) and in the list no two same words can repeat. We have made several helper methods
like search(Word* wl, char* wordStr), makeNode(char word) , addWord(Word head, char* word)

search-> takes head of the list and searches for the word we are looking for. Returns a pointer to the given word if found or returns the pointer to the last node in the list(this is useful when we have to add a new node to the end of the list) 

addWord-> takes the head of the list and it uses the search method. If the word is found, it increases the frequency by 1 or else add the new node to the end of the list. 

The main functioning of the program is done using wordFreq(Word* wl, char* filename, int fd1)
This function takes a newly initiated wordlist (currently empty) and a filename or a file descriptor. 

This makes our whole list of words along with their frequencies. 

Finally we have format_and_print(wl); which formats and gives us our final output using sprintf() and write()

link to video:
https://youtu.be/D5j2eF7SiH4

sources used:

https://www.geeksforgeeks.org/double-pointer-pointer-pointer-c/

https://ubuntuforums.org/showthread.php?t=1016188

===================================================================

Ritwik Bagga, Umair Afzal, Abhishek Dutt
