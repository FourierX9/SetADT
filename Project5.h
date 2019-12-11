#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Set.h"

/* Thank you Dr. Nandakumar for sharing this code*/
/*
 * Several of the required functions have been written already
 * You may use these functions as-is or you may modify them in any way.
 * Please NOTE, you are responsible for ensuring that the functions work correctly in
 * your project solution. Just because the function works correctly in my solution does
 * NOT mean that the function will work correctly in yours.
 */

/*
 * Design NOTES:
 *
 * The design provided in this starter kit assumes
 * (1) empty sets will be represented with length == 0 and elements == nullptr (i.e., address 0)
 * (2) amortized doubling is not used, and capacity is ignored/unused. Functions should assume that
 * the amount of storage available in the elements[] array is equal to length
 */



/* done for you already */
void destroySet(Set* self) {
    free(self->elements);
}

/* done for you already */
void createEmptySet(Set* self) {
    self->len = 0;
    self->elements = 0;
}

void createSingletonSet(Set* self, int x) {
    self->elements = (int*)malloc(sizeof(int));
    self->elements[0] = x;
    self->len = 1;
}

/* done for you already */
void createCopySet(Set* self, const Set* other) {
    self->elements = (int*) malloc(other->len * sizeof(int));
    for (int k = 0; k < other->len; k += 1) {
        self->elements[k] = other->elements[k];
    }
    self->len = other->len;
}

/*void assignSet(Set* self, const Set* other) {
	if (self == other) return;
	destroySet(self);

	createCopySet(self, other);
}*/

void assignSet(Set* self, const Set* other) {
    if (self == other) return;
    destroySet(self);

    createCopySet(self, other);
}

/* return true if x is an element of self */
bool isMemberSet(const Set* self, int x) {
    int is_found=false;
    int low = 0;
    int high = self->len-1;
    int i = (low + high) / 2;
    if (self->len == 0)
    {
        return false;
    }
    else
    {
        while (low < high)
        {
            if (self->elements[i] > x)
            {
                high = i - 1;
                i = (low + high) / 2;
            }
            else if (self->elements[i] == x)
            {
                is_found = true;
                return true;
            }
            else
            {
                low = i + 1;
                i = (low + high) / 2;
            }
        }
        if (self->elements[i] == x)
        {
            is_found = true;
            return true;
        }
        else
        {
            return is_found;
        }
    }
}

/*
 * add x as a new member to this set.
 * If x is already a member, then self should not be changed
 * Be sure to restore the design invariant property that elemnts[] remains sorted
 * (yes, you can assume it is sorted when the function is called, that's what an invariant is all about)
 */
/*
void insertSet(Set* self, int x) {
	int i = 0;
	int j = 0;
	int* p=NULL;
	if (self->len == 0)
	{
		while (p == NULL)
		{
			p = (int*)malloc(sizeof(int));
		}
		self->elements = p;
		self->elements[0] = x;
		self->len++;
	}
	else
	{
		if (x > self->elements[self->len - 1])
		{
			self->len++;
			while (p == NULL)
			{
				p = (int*)malloc((self->len) * sizeof(int));
			}
			for (i = 0; i < (self->len - 1); i++)
			{
				p[i] = self->elements[i];
			}
			self->elements = p;
			self->elements[self->len - 1] = x;
		}
		else {
			while (i < self->len)
			{
				if (x < self->elements[i])
				{
					self->len++;
					while (p == NULL)
					{
						p = (int*)malloc((self->len) * sizeof(int));
					}
					if (i == 0)
					{ }
					else
					{
						for (j = 0; j < i; j++)
						{
							p[j] = self->elements[j];
						}
					}
					p[j] = x;
					for (j = i+1; j < self->len; j++)
					{
						p[j] = self->elements[j - 1];
					}

					self->elements = p;
					break;
				}
				else if (x == self->elements[i])
				{
					return;
				}
				else
				{
					i++;
				}

			}
		}
	}
}*/

void insertSet(Set* self, int x) {
    int loc = -1;
    for (int i = 0; i < self->len; i++)
    {
        if (self->elements[i] == x) return;
        else if (x < self->elements[i])
        {
            loc = i;//locate x
            break;
        }
    }
    if (self->elements != 0) {//whether the set is empty
        self->len += 1;
        self->elements = (int*)realloc(self->elements, self->len * sizeof(int));
    }
    else {
        createSingletonSet(self, x);
        return;
    }

    if (loc != -1) {
        for (int i = self->len - 2; i >= loc; i--) {
            *(self->elements +i +1) = *(self->elements + i);
        }
        *(self->elements + loc) = x;
    }
    else {
        *(self->elements + (self->len - 1)) = x;
    }
}
/*
 * don't forget: it is OK to try to remove an element
 * that is NOT in the set.
 * If 'x' is not in the set 'self', then
 * removeSet should do nothing (it's not an error)
 * Otherwise, ('x' IS in the set), remove x. Be sure to update self->length
 * It is not necessary (nor recommended) to call malloc -- if removing an element means the
 * array on the heap is "too big", that's almost certainly OK, and reallocating a smaller array
 * is almost definitely NOT worth the trouble
 */
void removeSet(Set* self, int x) {
    int i = 0;
    int j = 0;
    int found = false;
    for (i = 0; i < self->len; i++)
    {
        if (self->elements[i] == x)
        {
            found = true;
            break;
        }
        else
        {
            continue;
        }
    }
    if (found == true)
    {
        int* p = (int*)malloc(sizeof(int) * (self->len - 1));
        /*if (i == 0)
        {

        }
        else if (i = self->len - 1)
        {

        }
        else
        {

        }*/
        for (j = 0; j < i; j++)
        {
            p[j] = self->elements[j];
        }
        for (j = i; j < self->len-1; j++)
        {
            p[j] = self->elements[j+1];
        }
        free(self->elements);
        self->elements = p;
        self->len--;
    }
    else
    {
        return;
    }
}

/* done for you already */
void displaySet(const Set* self) {
    int k;

    printf("{");

    if (self->len == 0) {
        printf("}");
    }
    else {
        for (k = 0; k < self->len; k += 1) {
            if (k < self->len - 1) {
                printf("%d,", self->elements[k]);
            } else {
                printf("%d}", self->elements[k]);
            }
        }
    }
}

/* return true if self and other have exactly the same elements */
bool isEqualToSet(const Set* self, const Set* other) {
    int i = 0;
    int j = 0;
    int is_equal = false;
    if (self->len != other->len)
    {
        return is_equal;
    }
    else
    {
        is_equal = true;
        while (i != self->len && j != other->len)
        {
            if (self->elements[i] != other->elements[j])
            {
                is_equal = false;
                break;
            }
            else
            {
                i++;
                j++;
            }
        }
        return is_equal;
    }
}

/* return true if every element of self is also an element of other */
bool isSubsetOf(const Set* self, const Set* other) {
    int i = 0;
    int j = 0;
    int is_Subset = false;
    if (self->len > other->len)
    {
        return is_Subset;
    }
    else
    {
        is_Subset = true;
        while (i != self->len && j != other->len)
        {
            if (self->elements[i] > self->elements[j])
            {
                j++;
                continue;
            }
            else if(self->elements[i] == self->elements[j])
            {
                i++;
                j++;
            }
            else if (self->elements[i] < self->elements[j])
            {
                is_Subset = false;
                return is_Subset;
            }
            if (self->elements[i] == self->elements[j])
            {
                return is_Subset;
            }
            else
            {
                return false;
            }
        }
        return is_Subset;
    }
}

/* done for you */
bool isEmptySet(const Set* self) {
    return self->len == 0;
}

/* remove all elements from self that are not also elements of other */
void intersectFromSet(Set* self, const Set* other) {
    int i = 0, j = 0;
    int* p;
    int length=0;
    p = (int*)malloc(self->len*sizeof(int));
    while (i < self->len && j<other->len)
    {
        if (self->elements[i] < other->elements[j])
        {
            i++;
            continue;
        }
        else if (self->elements[i] > other->elements[j])
        {
            j++;
            continue;
        }
        else
        {
            p[length] = self->elements[i];
            length++;
            i++;
            j++;
            continue;
        }
    }
    p = (int*)realloc(p, length * sizeof(int));
    free(self->elements);
    self->elements = p;
    if (p != NULL)
    {
        while (self->elements == NULL)
        {
            self->elements = p;
        }
    }
    else
    {
        self->elements = p;
    }
    self->len = length;
}

/* remove all elements from self that are also elements of other */
void subtractFromSet(Set* self, const Set* other) {
    Set* intersect;
    intersect = (Set*)malloc(sizeof(Set));
    /*intersect->elements = self->elements;
    intersect->len = self->len;*/
    createCopySet(intersect, self);
    int* p;
    int length = 0;
    p = (int*)malloc(self->len * sizeof(int));
    int i=0, j = 0;
    intersectFromSet(intersect, other);
    while(i<self->len&&j<intersect->len)//for (int i = 0; i < self->len; i++)
    {
        if (self->elements[i] < intersect->elements[j])
        {
            p[length] = self->elements[i];
            i++;
            length++;
            continue;
        }
        else if (self->elements[i] > intersect->elements[j])
        {
            if (j < intersect->len)
            {
                j++;
                continue;
            }
            else
            {
                break;
            }

        }
        else
        {
            i++;
            j++;
            continue;
        }
    }
    while (i < self->len)
    {
        p[length] = self->elements[i];
        i++;
        length++;
    }
    p = (int*)realloc(p, length * sizeof(int));
    free(self->elements);
    self->elements = p;
    self->len = length;
}

/* add all elements of other to self (obviously, without creating duplicate elements) */
/*void unionInSet(Set* self, const Set* other) {
	Set unionanswer;
	createEmptySet(&unionanswer);
	for (int i = 0; i < self->len; i++)
	{
		insertSet(&unionanswer, self->elements[i]);
	}
	for (int i = 0; i < other->len; i++)
	{
		insertSet(&unionanswer, other->elements[i]);
	}
	free(self->elements);
	self->elements = unionanswer.elements;
	self->len = unionanswer.len;
}
*/

void unionInSet(Set* self, const Set* other) {
    bool addO = false, addS = false;
    if (other->len == 0) {
        return;
    }
    if (self->len == 0) {
        addO = true;
    }

    //worst case, the union will be the sum of lengths (no matching elements)
    int* newElements = (int*)malloc((self->len + other->len) * sizeof(int));
    bool complete = false;
    int idxS = 0, idxO = 0, idxNew = 0;
    while (!complete) {
        if (addS) {
            *(newElements + idxNew) = *(self->elements + idxS);
            idxNew++;
            idxS++;
        }
        else if (addO) {
            *(newElements + idxNew) = *(other->elements + idxO);
            idxNew++;
            idxO++;
        }
        else if (*(other->elements + idxO) == *(self->elements + idxS)) {
            *(newElements + idxNew) = *(other->elements + idxO);
            idxO++;
            idxS++;
            idxNew++;
        }
        else if (*(other->elements + idxO) < *(self->elements + idxS)) {
            *(newElements + idxNew) = *(other->elements + idxO);
            idxNew++;
            idxO++;
        }
        else if (*(other->elements + idxO) > * (self->elements + idxS)) {
            *(newElements + idxNew) = *(self->elements + idxS);
            idxNew++;
            idxS++;
        }

        if ((idxS == self->len) && (idxO != other->len)) {
            addO = true;
        }
        else if ((idxS != self->len) && (idxO == other->len)) {
            addS = true;
        }
        else if ((idxS == self->len) && (idxO == other->len)) {
            complete = true;
        }
        else {
            complete = false;
        }
    }
    //free the previous elements in self
    free(self->elements);
    self->elements = newElements;
    self->len = idxNew;
}

