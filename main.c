#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Trie {
    int count;
    struct Trie* children[26];
};

void insert(struct Trie **ppTrie, char *word) {
    if (word == NULL || word[0] == '\0') {
        return;
    }
    if (ppTrie == NULL || *ppTrie == NULL) {
        *ppTrie = (struct Trie*)calloc(1, sizeof(struct Trie));
    }
    struct Trie *temp = *ppTrie;
    int len = strlen(word);
    for (int i = 0; i < len; ++i) {
        int index = word[i] - 'a';
        if (temp->children[index] == NULL) {
            struct Trie *new = (struct Trie*)calloc(1, sizeof(struct Trie));
            temp->children[index] = new;
        }
        temp = temp->children[index];
    }
    temp->count++;
}

int numberOfOccurances(struct Trie *pTrie, char *word) {
    if (pTrie == NULL) {
        return 0;
    }
    if (word == NULL || word[0] == '\0') {
        return 0;
    }
    int len = strlen(word);
    for (int i = 0; i < len; ++i) {
        pTrie = pTrie->children[word[i] - 'a'];
        if (pTrie == NULL) {
            return 0;
        }
    }
    return pTrie->count;
}

struct Trie *deallocateTrie(struct Trie *pTrie) {
    if (pTrie == NULL) {
        return NULL;
    }
    for (int i = 0; i < 26; ++i) {
        pTrie->children[i] = deallocateTrie(pTrie->children[i]);
    }
    free(pTrie);
    return NULL;
}

int main(void)
{
    struct Trie *trie = NULL;
    //read the number of the words in the dictionary
    // parse line  by line, and insert each word to the trie data structure
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    int size = 5;

    for (int i = 0; i < size; ++i) {
        insert(&trie, pWords[i]);
    }

    for (int i=0;i<size;i++)
    {
        printf("\t%s : %d\n",pWords[i], numberOfOccurances(trie, pWords[i]));
    }
    trie = deallocateTrie(trie);
    if (trie != NULL)
       printf("There is an error in this program\n");
    return 0;
}
