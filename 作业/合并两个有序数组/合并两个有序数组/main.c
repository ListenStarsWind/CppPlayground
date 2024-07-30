#define _CRT_SECURE_NO_WARNINGS

void merge(int* nums1, int nums1Size, int m, int* nums2, int nums2Size, int n) {
    int source1 = m - 1;
    int source2 = n - 1;
    int destination = nums1Size - 1;
    while ((source1 >= 0) && (source2 >= 0)) {
        if (nums1[source1] < nums2[source2]) {
            nums1[destination--] = nums2[source2--];
        }
        else {
            nums1[destination--] = nums1[source1--];
        }
    }
    while (source2 >= 0) {
        nums1[destination--] = nums2[source2--];
    }
}