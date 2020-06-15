//typedef struct {
//    short ch;
//    short id;
//    size_t first_child;
//    size_t second_child;
//    size_t third_child;
//    size_t fourth_child;
//} Node;


//__kernel void add(ulong n, global const char *input, global char *output, global Node *trie) {
//    size_t currentIndex = get_global_id(0);
//    printf("%d", currentIndex);
//    if(currentIndex < n) {
//        size_t nextIndex;
//        char currentLetter = input[currentIndex];
//        Node currentNode = trie[0];
//        int childIndex;
//    //    printf("%c", currentNode.ch);
//
//        while(true) {
//            printf("%c", currentNode.ch);
//            if(currentLetter == 'A') childIndex = currentNode.first_child;
//            if(currentLetter == 'C') childIndex = currentNode.second_child;
//            if(currentLetter == 'T') childIndex = currentNode.third_child;
//            if(currentLetter == 'G') childIndex = currentNode.fourth_child;
//    //        printf("%d", childIndex);
//
//            if(childIndex == 0) return;
//            else {
//                nextIndex = childIndex;
//                currentIndex++;
//                currentLetter = input[currentIndex];
//                currentNode = trie[nextIndex];
//                if (currentNode.id != 0) printf("%d\n", currentNode.id);
//            }
//        }
//    }
//}


__kernel void add(ulong n, global const char *input, global char *output, global char *chs, global char *ids, global char *firsts, global char *seconds, global char *thirds, global char *fourths) {
    size_t currentIndex = get_global_id(0);
    if(currentIndex < n) {
        size_t nextIndex = 0;
        char currentLetter = input[currentIndex];
        int childIndex;

        while(true) {
            if(currentLetter == 'A'){
                childIndex = firsts[nextIndex];
            }
            else if(currentLetter == 'C') childIndex = seconds[nextIndex];
            else if(currentLetter == 'T') childIndex = thirds[nextIndex];
            else if(currentLetter == 'G') childIndex = fourths[nextIndex];
            else return;

            if(childIndex == 0) return;
            else {
                nextIndex = childIndex;
                if(currentIndex >= n) return;

                if (ids[nextIndex] != -1) printf("%d\n", ids[nextIndex]);
                currentIndex++;
                currentLetter = input[currentIndex];
            }
        }
    }
}