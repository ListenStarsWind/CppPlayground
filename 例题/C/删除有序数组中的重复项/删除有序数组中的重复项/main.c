#define _CRT_SECURE_NO_WARNINGS

int removeDuplicates(int* nums, int numsSize) {
    int destination = 0;
    int source = 0;
    while (source < numsSize) {
        if (nums[destination] != nums[source]) {
            nums[++destination] = nums[source++];
        }
        else {
            source++;
        }
    }
    return destination + 1;
}