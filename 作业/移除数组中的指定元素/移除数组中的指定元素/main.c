#define _CRT_SECURE_NO_WARNINGS

int removeElement(int* nums, int numsSize, int val) {
    int source = 0;
    int destination = 0;
    while (source < numsSize) {
        if (nums[source] == val) {
            source++;
        }
        else {
            nums[destination++] = nums[source++];
        }
    }
    return destination;
}