#include "ft_nm.h"

// Concession made. will not compare exactly like original code as it uses strcoll and LOCALE data for comparison.
// This function will compare the strings in a case-insensitive manner, ignoring underscores and dots.
static int strip_and_comp(char *Lname, char *Rname)
{
	int i = 0;
	int j = 0;
	while (Lname[i] && Rname[j]) {
		if (!ft_isalnum(Lname[i])) {
			i++;
			continue;
		}
		else if (!ft_isalnum(Rname[j])) {
			j++;
			continue;
		}
		else {
			char c1 = ft_tolower((unsigned char)Lname[i]);
			char c2 = ft_tolower((unsigned char)Rname[j]);
			if (c1 != c2)
				return c1 - c2;
			i++;
			j++;
		}
	}
	return ((unsigned char)Lname[i] - (unsigned char)Rname[j]);
}

static void merge(sym_t *array, int left, int mid, int right)
{
	int i, j, k;
	int n1 = mid - left + 1;
	int n2 = right - mid;

	sym_t L[n1];
	sym_t R[n2];

	for (i = 0; i < n1; i++)
		L[i] = array[left + i];
	for (j = 0; j < n2; j++)
		R[j] = array[mid + 1 + j];

	i = 0; // Initial index of first sub-array
	j = 0; // Initial index of second sub-array
	k = left; // Initial index of merged sub-array

	while (i < n1 && j < n2) {
		if (strip_and_comp(L[i].name, R[j].name) <= 0) {
			array[k] = L[i];
			i++;
		} else {
			array[k] = R[j];
			j++;
		}
		k++;
	}

	while (i < n1) {
		array[k] = L[i];
		i++;
		k++;
	}

	while (j < n2) {
		array[k] = R[j];
		j++;
		k++;
	}
}

static void reverse_merge(sym_t *array, int left, int mid, int right)
{
	int i, j, k;
	int n1 = mid - left + 1;
	int n2 = right - mid;

	sym_t L[n1];
	sym_t R[n2];

	for (i = 0; i < n1; i++)
		L[i] = array[left + i];
	for (j = 0; j < n2; j++)
		R[j] = array[mid + 1 + j];

	i = 0; // Initial index of first sub-array
	j = 0; // Initial index of second sub-array
	k = left; // Initial index of merged sub-array

	while (i < n1 && j < n2) {
		if (strip_and_comp(L[i].name, R[j].name) >= 0) {
			array[k] = L[i];
			i++;
		} else {
			array[k] = R[j];
			j++;
		}
		k++;
	}

	while (i < n1) {
		array[k] = L[i];
		i++;
		k++;
	}

	while (j < n2) {
		array[k] = R[j];
		j++;
		k++;
	}
}



void merge_sort(sym_t *array, int left, int right)
{
	if (left < right)
	{
		int mid = (left + right) / 2;
		merge_sort(array, left, mid);
		merge_sort(array, mid + 1, right);
		merge(array, left, mid, right);
	}
}

void reverse_merge_sort(sym_t *array, int left, int right)
{
	if (left < right)
	{
		int mid = (left + right) / 2;
		reverse_merge_sort(array, left, mid);
		reverse_merge_sort(array, mid + 1, right);
		reverse_merge(array, left, mid, right);
	}
}
