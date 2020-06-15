typedef struct {
    short ch;
    int num;
    short id;
    size_t first_child;
    size_t second_child;
    size_t third_child;
    size_t fourth_child;
} Node;


__kernel void add(ulong n, global const char *input, global char *output, global Node *trie) {
    size_t currentIndex = get_global_id(0);

    if(currentIndex < n) {
        size_t nextIndex;
        char currentLetter = input[currentIndex];
        Node currentNode = trie[0];
        int childIndex;
    //    printf("%c", currentNode.ch);

        while(true) {
            printf("%c", currentNode.ch);
            if(currentLetter == 'A') childIndex = currentNode.first_child;
            if(currentLetter == 'C') childIndex = currentNode.second_child;
            if(currentLetter == 'T') childIndex = currentNode.third_child;
            if(currentLetter == 'G') childIndex = currentNode.fourth_child;
    //        printf("%d", childIndex);

            if(childIndex == 0) return;
            else {
                nextIndex = childIndex;
                currentIndex++;
                currentLetter = input[currentIndex];
                currentNode = trie[nextIndex];
                if (currentNode.id != 0) printf("%d\n", currentNode.id);
            }
        }
    }
}