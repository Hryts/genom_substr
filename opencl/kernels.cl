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