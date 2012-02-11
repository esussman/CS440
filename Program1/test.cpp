/* 
 * Run with
 * 
 *    -i iterations
 *
 * to do a stress test for the given number of iterations.
 */

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <set>
#include <vector>

#include "Person.hpp"
#include "List.hpp"

/*
 * Person hierarchy print functions.
 * These are not intended to be member functions, but more like
 * non-member helper functions.
 */

void
Person_print(Person *p) {
    printf("Name: %s\n", p->name);
    printf("Gender: %c\n", p->gender);
}

void
Student_print(Student *s) {
    printf("Major: %s\n", s->major);
}

void
Under_print(Under *u) {
    printf("Year: %d\n", u->year);
}

void
Grad_print(Grad *g) {
    printf("Degree: %s\n", g->degree);
}

void
Professor_print(Professor *p) {
    printf("Office: %s\n", p->office);
}

/*
 * List test functions.
 */

typedef Person *PersonPtr;

// Comparison function, used later.
bool
PersonPtr_less(const PersonPtr &p1, const PersonPtr &p2) {
    return strcmp(p1->name, p2->name) < 0;
}
// This "instantiates" the template.
// Note that there is no semicolon.
List_DEFINE(PersonPtr)

// MyClass List
struct MyClass {
    double num;
};
bool
MyClass_less(const MyClass &o1, const MyClass &o2) {
    return o1.num < o2.num;
}
List_DEFINE(MyClass)

// int List
bool
int_less(const int &i1, const int &i2) {
    return i1 < i2;
}
List_DEFINE(int)

// Stress test List
struct Stress {
    int val;
    Stress(int _v) : val(_v){}
};
bool
Stress_less(const Stress& o1, const Stress& o2) {
    return o1.val < o2.val;
}
List_DEFINE(Stress)



/*
 * Additional test functions for List.
 */

void traverse(List_PersonPtr &l, int level);
void traverse2(int level);
void check(List_Stress *list, std::set<int> &mirror);

// Below is a helper function for the testing only.  It not necessary for the
// actual container.
bool
Stress_Iterator_less(const List_Stress_Iterator& lhs, const List_Stress_Iterator& rhs) {
    List_Stress_Iterator it1, it2;
    it1 = lhs;
    it2 = rhs;
    Stress s1 = it1.deref(&it1);
    Stress s2 = it2.deref(&it2);
    return s1.val < s2.val;
}

/*
 * Main.
 */

void
print(List_PersonPtr *list) {
    printf("---- Print begin\n");
    List_PersonPtr_Iterator it = list->begin(list);
    while (!List_PersonPtr_Iterator_equal(it, list->end(list))) {
        printf("    %s\n", it.deref(&it)->name);
        it.inc(&it);
    }
    printf("---- Print end\n");
}

int
main(int argc, char *argv[]) {

    int c;
    int iterations = 0;
    while ((c = getopt(argc, argv, "i:")) != EOF) {
        switch (c) {
            case 'i':
                iterations = atoi(optarg);
                break;
            case '?':
                fprintf(stderr, "Unrecog.\n");
                exit(1);
        }
    }

    srand48(1234);

    /**************************************************************************
     * Test Part 1, Person hierarchy.
     */

    Person *p1 = 0;
    {
        /*
         * Create an Under object.
         */

        printf("---- Under\n");

        char *n = strdup("Jane");
        char *major = strdup("CS");
        // Pass allocated strings to prevent the implementation from
        // just saving the pointers, which would be possible if we
        // passed literals.
        p1 = (Person *) Under_new(n, 'F', major, 4);
        free(n);
        free(major);
        
        // Prints:
        // Name: <name>
        // Gender: <gender>
        Person_print(p1);
        // Note that Grad and Under print the same thing for work,
        // and so can share the implementation.
        p1->work(p1); // Prints "<name> studies <major>."

        Student *s = Person_downcast_Student(p1); // Must return null if not a Student.
        Student_print(s); // Prints "Major: <major>"
        // Assume year 4 means one more year to go.
        s->graduate(s); // Prints "<name> graduates in <N> years and finds a job in <major> or goes to grad school."

        Under *u = Person_downcast_Under(p1); // Must return null if not an Under.
        assert(Student_downcast_Under(s) == u);
        Under_print(u); // Prints "Year: <year>"

        // Check that upcast still works right.
        assert((Person *) u == p1);

        // Check that other downcasts fail.
        assert(Person_downcast_Grad(p1) == 0);
        assert(Person_downcast_Professor(p1) == 0);
        assert(Student_downcast_Grad(s) == 0);
    }

    Person *p2 = 0;
    {
        /*
         * Create an Grad object.
         */

        printf("---- Grad\n");

        char *n = strdup("John");
        char *major = strdup("Biology");
        char *degree = strdup("PhD");
        p2 = (Person *) Grad_new(n, 'M', major, degree);
        free(n);
        free(major);
        free(degree);
        
        Person_print(p2);
        p2->work(p2); // Same as Under.

        Student *s = Person_downcast_Student(p2);
        Student_print(s);
        s->graduate(s); // Prints "<name> graduates with a <degree> and finds a job in <major>."

        Grad *g = Person_downcast_Grad(p2);
        assert(Student_downcast_Grad(s) == g);
        Grad_print(g); // Prints "Degree: <degree>"

        // Check that other downcasts fail.
        assert(Person_downcast_Under(p2) == 0);
        assert(Person_downcast_Professor(p2) == 0);
        assert(Student_downcast_Under(s) == 0);
    }

    Person *p3 = 0;
    {
        /*
         * Create an Professor object.
         */

        printf("---- Professor\n");

        char *name = strdup("Mary");
        char *office = strdup("T-10");
        p3 = (Person *) Professor_new(name, 'F', office);
        free(name);
        free(office);
        
        Person_print(p3);
        p3->work(p3); // Prints "<name> teaches."

        Professor *p = Person_downcast_Professor(p3);
        Professor_print(p); // Prints "Office: <office>"
        p->research(p, "computers"); // Must print "<name> does research in <topic>."
        p->research(p, "frogs");

        // Check that other downcasts fail.
        assert(Person_downcast_Student(p3) == 0);
        assert(Person_downcast_Under(p3) == 0);
        assert(Person_downcast_Grad(p3) == 0);
    }

    Person *p4 = (Person *) Under_new("Dave", 'M', "Chemistry", 2);

    /**************************************************************************
     * Test Part 2, List template.
     */

    /*
     * Test with Person.
     */

    {
        // This creates a List of pointers to Person objects.  It corresponds to
        // what in real C++ might be std::set<Person *>.  Note that it is not a
        // List of Person objects, but rather of _pointers_ to Person
        // objects.
        List_PersonPtr *list = List_PersonPtr_new(PersonPtr_less);

        // Should print "---- List_PersonPtr, 15".
        printf("---- %s, %d\n", list->type, (int) sizeof(list->type));

        // Insert people into the List.
        list->push_front(list, p1);
        print(list);
        list->push_front(list, p2);
        print(list);
        list->push_front(list, p3);
        print(list);
        list->push_front(list, p4);
        print(list);

        // Check iterator equality.
        {
            // Returns an iterator pointing to the first element.
            List_PersonPtr_Iterator it1 = list->begin(list);
            // Returns an iterator pointing to one PAST the last element.  This
            // iterator is obviously conceptual only.  It cannot be dereferenced.
            List_PersonPtr_Iterator it2 = list->end(list);

            // inc() advances the iterator forward.  dec() decrements the iterator
            // so it points to the preceding element.
            it1.inc(&it1); // Second node now.
            it1.inc(&it1); // Third node now.
            it2.dec(&it2); // Fourth node now.
            it2.dec(&it2); // Third node now.
            assert(List_PersonPtr_Iterator_equal(it1, it2));
            it2.dec(&it2); // Second node now.
            it2.dec(&it2); // First node now.
            assert(List_PersonPtr_Iterator_equal(list->begin(list), it2));
        }

        // Simple sort check.
        {
            list->sort(list);
            printf("---- Should be sorted now\n");
            print(list);
        }

        // Check push_front return value.
        {
            printf("---- Test push_front() return.\n");
            // Insert returns an interator.  The iterator points to the
            // element, and can be used to erase the element.
            Person *pp = (Person *) Professor_new("Larry", 'M', "F9");
            List_PersonPtr_Iterator it = list->push_front(list, pp);
            Person_print(it.deref(&it));
            list->erase(list, it);
            pp->delet(pp);
        }

        // Print the whole thing now, to verify ordering.
        printf("---- Before erasures.\n");

        // Iterate through the whole List, and call work() on each
        // Person.  deref() returns what the iterator was pointing to.
        for (List_PersonPtr_Iterator it = list->begin(list);
         !List_PersonPtr_Iterator_equal(it, list->end(list)); it.inc(&it)) {
            Person *p = it.deref(&it);
            p->work(p);
        }

        // Test multiple traversals of the same List.
        printf("---- Multiple traversals\n");
        traverse(*list, 3);

        // Test multiple List at the same time.
        printf("---- Multiple List\n");
        traverse2(4);

        /*
         * Test some erasures.
         */

        // Erase first element.
        list->erase(list, list->begin(list));
        List_PersonPtr_Iterator it = list->end(list);
        it.dec(&it); // it now points to last element.
        it.dec(&it); // it now points to penultimate element.
        list->erase(list, it);

        printf("---- After erasures.\n");

        // Iterate through the whole List, and call work() on each
        // Person.
        for (List_PersonPtr_Iterator it = list->begin(list);
         !List_PersonPtr_Iterator_equal(it, list->end(list)); it.inc(&it)) {
            Person *p = it.deref(&it);
            p->work(p);
        }

        // Test iterator validity.
        {
            // Iterators must be valid even when other things are inserted.
            printf("---- Test iterator non-invalidation\n");

            Person *pp = (Person *) Professor_new("Zeke", 'M', "F9");
            // Will be at the end.
            List_PersonPtr_Iterator it = list->push_back(list, pp);
            // Delete first, iterator should still be valid.
            List_PersonPtr_Iterator b = list->begin(list);
            Person *tmp = b.deref(&b); // Save, so we can reinsert.
            list->erase(list, list->begin(list)); // Erase it.
            Person_print(it.deref(&it)); // This should still be valid.
            list->push_back(list, tmp); // Reinsert.
            list->erase(list, it); // Erase.
            pp->delet(pp); // Cleanup.
        }

        // Must not delete the actual Person objects.  Note that we cannot use
        // 'delete', because it is a reserved word (keyword).
        list->delet(list);

        // Note that these functions must cleanup after the derived object.  For
        // example, if p1 is a Under, delet() must cleanup after Under.  These are
        // what we call "virtual destructors", which we will talk about more later.
        p1->delet(p1);
        p2->delet(p2);
        p3->delet(p3);
        p4->delet(p4);
    }

    /*
     * Test List with MyClass.
     */

    {
        MyClass m1, m2, m3, m4, m5;
        m1.num = 0;
        m2.num = 3;
        m3.num = 1;
        m4.num = 2;
        m5.num = -999;
        List_MyClass* list = List_MyClass_new(MyClass_less);

        // Should print "---- List_MyClass, 13".
        printf("---- %s, %d\n", list->type, (int) sizeof(list->type));

        List_MyClass_Iterator it;
        // Empty container, should print nothing.
        for (it = list->begin(list);
         !List_MyClass_Iterator_equal(it, list->end(list)); it.inc(&it)) {
            MyClass m = it.deref(&it);
            printf("%3.1f ", m.num);
        }
        printf("\n");

        list->push_back(list, m1);
        list->push_front(list, m2);
        list->push_back(list, m3);
        list->push_back(list, m4);
        list->sort(list);

        // Should print 0.0 1.0 2.0 3.0
        for (it = list->begin(list);
         !List_MyClass_Iterator_equal(it, list->end(list)); it.inc(&it)) {
            MyClass m = it.deref(&it);
            printf("%3.1f ", m.num);
        }
        printf("\n");

        // Erase the first element.
        list->erase(list, list->begin(list));
        // Should print "1.0 2.0 3.0".
        for (it = list->begin(list);
         !List_MyClass_Iterator_equal(it, list->end(list)); it.inc(&it)) {
            MyClass m = it.deref(&it);
            printf("%3.1f ", m.num);
        }
        printf("\n");

        // Erase the new first element.
        list->erase(list, list->begin(list));
        // Should print "2.0 3.0".
        for (it = list->begin(list);
         !List_MyClass_Iterator_equal(it, list->end(list)); it.inc(&it)) {
            MyClass m = it.deref(&it);
            printf("%3.1f ", m.num);
        }
        printf("\n");

        // Erase the element in the end.
        it = list->end(list);
        it.dec(&it); // It now points to last element.
        list->erase(list, it);
        // Should print "2.0".
        for (it = list->begin(list);
         !List_MyClass_Iterator_equal(it, list->end(list)); it.inc(&it)) {
            MyClass m = it.deref(&it);
            printf("%3.1f ", m.num);
        }
        printf("\n");

        // Erase the last element.
        list->erase(list, list->begin(list));
        // Should print nothing.
        for (it = list->begin(list);
                !List_MyClass_Iterator_equal(it, list->end(list)); it.inc(&it)) {
            MyClass m = it.deref(&it);
            printf("%3.1f ", m.num);
        }
        printf("\n");

        list->delet(list);
    }

    /*
     * Test List with plain int.
     */

    {
        List_int* list = List_int_new(int_less);
        // Should print "---- List_int, 9".
        printf("---- %s, %d\n", list->type, (int) sizeof(list->type));

        List_int_Iterator it; 
        // Empty container, should print nothing.
        for (it = list->begin(list);
         !List_int_Iterator_equal(it, list->end(list)); it.inc(&it)) {
            printf("%d ", it.deref(&it));
        }
        printf("\n");

        list->push_back(list, 4);
        list->push_back(list, 3);
        list->push_back(list, 0);
        list->push_back(list, 2);
        list->push_back(list, 1);
        list->sort(list);

        // Should print "0 1 2 3 4".
        for (it = list->begin(list);
         !List_int_Iterator_equal(it, list->end(list)); it.inc(&it)) {
            printf("%d ", it.deref(&it));
        }
        printf("\n");

        // Insert dupes.
        list->push_back(list, 4);
        list->push_back(list, 3);
        list->push_back(list, 0);
        list->push_back(list, 2);
        list->push_back(list, 1);
        list->sort(list);
        // Should print "0 0 1 1 2 2 3 3 4 4".
        for (it = list->begin(list);
         !List_int_Iterator_equal(it, list->end(list)); it.inc(&it)) {
            printf("%d ", it.deref(&it));
        }
        printf("\n");

        // Erase the first element.
        list->erase(list, list->begin(list));

        // Erase the new first element.
        list->erase(list, list->begin(list));

        // Erase the element in the end.
        it = list->end(list);
        it.dec(&it); // It now points to last element.
        list->erase(list, it);
        // Should print "2 3".
        for (it = list->begin(list); !List_int_Iterator_equal(it, list->end(list)); it.inc(&it)) 
            printf("%d ", it.deref(&it));
        printf("\n");

        // Erase all elements.
        list->erase(list, list->begin(list));
        list->erase(list, list->begin(list));
        // Should print nothing.
        for (it = list->begin(list); !List_int_Iterator_equal(it, list->end(list)); it.inc(&it)) 
            printf("%d ", it.deref(&it));
        printf("\n");

        list->delet(list);
    }

    /*
     * Stress test List.
     */

    #if 0
    if (iterations > 0) {
        List_Stress* list = List_Stress_new(Stress_less);
        typedef std::list<int> mirror_t;
        mirror_t mirror;
        typedef std::set<List_Stress_Iterator, bool(*)(const List_Stress_Iterator& lhs, const List_Stress_Iterator& rhs)> iters_t;
        iters_t iters(&Stress_Iterator_less);

        std::cout << "---- Starting stress test:" << std::endl;

        const int N = iterations;

        srand(9757);
        int n_inserted = 0, n_erased = 0, n_iters_changed = 0, n_empty = 0, n_dupes = 0;
        double avg_size = 0;

        for (int i = 0; i < N; ++i) {

            double op = drand48();

            // The probability of removal should be slightly higher than the
            // probability of insertion so that the List is often empty.
            if (op < .44) {

                /*
                // Insert an element.  Repeat until no duplicate.
                do {
                    int v = rand();
                    std::pair<mirror_t::iterator, bool> res = mirror.insert(v);
                    List_Stress_Iterator it = list->insert(list, Stress(v));
                    if (res.second) {
                        // If insert into mirror succeeded, insert into List should also have succeeded.
                        assert(!List_Stress_Iterator_equal(it, list->end(list)));
                        // Store the iterator.
                        iters.insert(it);
                        break;
                    }
                    // If insert into mirror did not succeed, insert into List
                    // should also not have succeeded, in which case, we
                    // generate another value to store.
                    assert(List_Stress_Iterator_equal(it, list->end(list)));
                    n_dupes++;
                } while (true);
                */

                List_Stress_Iterator it;
                if (drand48() < .5) {
                    // Do push_front().
                    int v = rand();
                    mirror.push_back(v);
                    it = list->push_back(v);
                } else {
                    // Do push_back().
                    int v = rand();
                    mirror.push_back(v);
                    it = list->push_back(v);
                }
                iters.insert(it);

                ++n_inserted;
                 
            } else if (op < .90) {

                // Erase an element.
                if (iters.size() != 0) {

                    // Pick a random index.
                    int index = rand()%iters.size();
                    iters_t::iterator iit = iters.begin();
                    while(index--) {
                        ++iit;
                    }

                    List_Stress_Iterator it = *iit;
                    // The iterator should not be end()
                    assert(!List_Stress_Iterator_equal(it, list->end(list)));

                    Stress s = it.deref(&it);
                    mirror.erase(s.val);
                    iters.erase(iit);
                    list->erase(list, it);

                    ++n_erased;
                }

            } else {

                // Increment or decrement an iterator.

                // Size of containers should be same
                assert(iters.size() == mirror.size());

                // If the container is empty, skip
                if (iters.size() != 0) {

                    // Pick a random index
                    int index = rand()%iters.size();
                    iters_t::iterator iters_it = iters.begin();
                    while (index--) {
                        ++iters_it;
                    }

                    List_Stress_Iterator it = *iters_it;
                    // The iterator should not be end().
                    assert(!List_Stress_Iterator_equal(it, list->end(list)));

                    // If it is the begin(), then only increment,
                    // otherwise, pick either forward or backward.
                    if (List_Stress_Iterator_equal(it, list->begin(list))) {
                        it.inc(&it);
                        ++iters_it;
                    } else {
                        if (rand()%2 == 0) {
                            it.inc(&it);
                            ++iters_it;
                        } else {
                            it.dec(&it);
                            --iters_it;
                        }
                    }
                    // If we didn't hit the end, replace the resulting iterator
                    // in the iterator list.
                    if (!List_Stress_Iterator_equal(it, list->end(list))) {
                        assert(List_Stress_Iterator_equal(it, *iters_it));
                        iters.erase(iters_it);
                        iters.insert(it);
                    }
                }

                ++n_iters_changed;
            }

            avg_size += double(iters.size())/N;

            if (iters.size() == 0) {
                ++n_empty;
            }

            check(list, mirror);
        }

        std::cout << "inserted: " << n_inserted << " times" << std::endl;
        std::cout << "erased: " << n_erased << " times" << std::endl;
        std::cout << "iterators changed: " << n_iters_changed << " times" << std::endl;
        std::cout << "empty count: " << n_empty << std::endl;
        std::cout << "avg size: " << avg_size << std::endl;
        // std::cout << "n dupes: " << n_dupes << std::endl;

        list->delet(list);
    }
    #endif
}

#if 0
void
check(List_Stress *list, std::set<int> &mirror) {

    // Check if the reference container and stress container is identical
    List_Stress_Iterator it = list->begin(list);
    std::set<int>::iterator mit = mirror.begin();

    for( ; !List_Stress_Iterator_equal(it, list->end(list)) && mit != mirror.end(); it.inc(&it), ++mit) {
        Stress e = it.deref(&it);
        if (e.val != *mit) {
            fprintf(stderr, "Reference tree and test tree differ.\n");
            abort();
        }
    }

    if(!List_Stress_Iterator_equal(it, list->end(list)) || mit!=mirror.end()) {
        fprintf(stderr, "Reference tree and test tree differ.\n");
        abort();
    }
}
#endif

// Test single list being traversed by multiple iterators simultaneously.
void
traverse(List_PersonPtr &list, int level) {
    for (List_PersonPtr_Iterator it = list.begin(&list); !List_PersonPtr_Iterator_equal(it, list.end(&list)); it.inc(&it)) {
        Person_print(it.deref(&it));
        if (level != 0) {
            traverse(list, level - 1);
        }
    }
}

// Test multiple lists.
void
traverse2(int level) {

    List_PersonPtr *list = List_PersonPtr_new(PersonPtr_less);

    struct Local {
        static Person *person() {
            char name[30];
            sprintf(name, "Jane%d", int(10000*drand48()));
            return (Person *) Professor_new(name, 'F', "T-10");
        }
    };

    for (int i = 0; i < 4; i++) {
        Person *p = Local::person();
        List_PersonPtr_Iterator it = list->push_back(list, p);
        // If a duplicate (unlikely but possible), free it, because it
        // didn't get inserted.
        if (List_PersonPtr_Iterator_equal(it, list->end(list))) {
            p->delet(p);
        }
    }

    for (List_PersonPtr_Iterator it = list->begin(list);
     !List_PersonPtr_Iterator_equal(it, list->end(list));
     it.inc(&it)) {
        Person_print(it.deref(&it));
        if (level != 0) {
            traverse2(level - 1);
        }
    }

    // Remove from List before deleting, to avoid having pointers to
    // deleted Person objects in the List, which can mess up
    // some algorithms for incrementing.
    {
        std::vector<Person *> del_list;
        for (List_PersonPtr_Iterator it = list->begin(list);
         !List_PersonPtr_Iterator_equal(it, list->end(list));
         it.inc(&it)) {
            del_list.push_back(it.deref(&it));
        }

        list->delet(list);

        for (size_t i = 0; i < del_list.size(); i++) {
            del_list.at(i)->delet(del_list.at(i));
        }
    }
}
