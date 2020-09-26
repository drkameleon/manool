---
title:   Lesson 4 -- Tutorial
updated: 2020-06-01
---

<aside markdown="1" class="right">
Lesson 4 of 5 -- Tutorial
=========================
+ [Lesson 1](lesson-1#start)
+ [Lesson 2](lesson-2#start)
+ **[Previous Lesson](lesson-3#start)**
+ **[Next Lesson](lesson-5#start)**
</aside>

{%include page_header.md%}{%raw%}


Composite Data Types, For-Loops and Views
----------------------------------------------------------------------------------------------------------------------------------------------------------------

MANOOL provides a comprehensive set of composite data types, which vary in basic operations and internal data structure (and thus in asymptotic complexity of
basic operations with composite values).[^a1]

[^a1]: A composite value in MANOOL (or object, depending on your point of view) incorporates other values (or objects, respectively). This happens irrespective
       of component types and without placing restrictions on the number of components on behalf of the composite type itself. Thus, complex numbers, for
       instance, are not composite values according to this definition.

The following examples should allow you to master composite types of MANOOL and deal easily and efficiently with elaborate data sets. Pay special attention to
comments embedded in these examples about asymptotic complexity of certain expressions (such as `/*O(1)*/` or `/*O(log n)*/`).[^a2]

[^a2]: Complete control over time complexity of operations with composite values may be the whole point of using MANOOL in the first place.

Normally, you can iterate over elements of a composite value in a straightforward way by using a `for`-loop:[^a3]

    { {extern "manool.org.18/std/0.6/all"} in
    : for { E = {array of "Red" "Orange" "Yellow" "Green" "Blue" "Indigo" "Violet"}$ } do
      Out.WriteLine[E]
    }

  (here we construct an _array_ out of elements by using the expression `{array of ...}` and declare the variable `E` as a `for`-loop variable).

[^a3]: Components of an iterable composite value are also referred to as _elements_ of that value.

Output:

    Red
    Orange
    Yellow
    Green
    Blue
    Indigo
    Violet

You can apply the operation `Size` to any iterable composite value to obtain the number of elements in the argument. Actually, you always iterate over elements
of a _view_ (some composite values are views onto their own elements).[^a4]

[^a4]: `{for {E = C} in ...}` is actually equivalent to `{for {E = C.Elems[]} in ...}`, and `Elems` for a view shall return that view again. Other operations
       exist that return views, like `Keys`, which returns a view onto access keys for a composite value.

<aside markdown="1">

One kind of view, which is not a full-blown composite data type, is the range (of integral values):

    {{extern "manool.org.18/std/0.6/all"} in: for { E = Range[7]$ } do Out.WriteLine[E]}

Output:

    0
    1
    2
    3
    4
    5
    6

A range consists of all integers between its _low_ bound and up to but not including its _high_ bound, both passed to a `Range` constructor (`Range[7]` is a
shorthand for `Range[0; 7]`). You can even construct reversed ranges by using `RevRange` instead of `Range` (with the same arguments):

    {{extern "manool.org.18/std/0.6/all"} in: for { E = RevRange[7]$ } do Out.WriteLine[E]}

Output:

    6
    5
    4
    3
    2
    1
    0

</aside>

#### Concatenation and slicing of arrays and sequences, move operations

You can concatenate arrays and get subarrays (_slices_ in more general terms), even in reverse order if you like, by indexing (subscripting) using ranges:[^a5]

    { {extern "manool.org.18/std/0.6/all"} in
    : var { A = {array of "Red" "Orange" "Yellow" "Green" "Blue" "Indigo" "Violet"}$ } in
    : for { E = A[Range[2; Size[A]]] + A[RevRange[Size[A] - 1]] } do
      Out.WriteLine[E]
    }

[^a5]: You can also access individual array elements (by index), which is demonstrated later.

Compared to arrays, sequences (another composite data type) may be more efficient for concatenation and removing a few elements from either end. In turn, arrays
are more efficient than sequences for accessing individual elements in the middle. Otherwise, they are similar:

    { {extern "manool.org.18/std/0.6/all"} in
    : var { S = {sequence of "Red" "Orange" "Yellow" "Green" "Blue" "Indigo" "Violet"} } in
    : var { R = S[RevRange[Size[S]]] } in
    : for { E = S![Range[2; Size[S]]] + R![Range[1; Size[R]]] /*O(1)*/ } do
      Out.WriteLine[E]
    }

The constructs `S!` and `R!` above refer to _move_ operations. By using a move operation, you roughly tell the MANOOL translator: "I declare that I won't need
the value stored in this location anymore. Please feel free to reuse any associated resources as you wish.".[^a6]

[^a6]: If you in fact hold your promise, such move operation is semantically a non-op, but it may be crucial for efficiency. Arguably, relying on move
       operations instead of referential semantics constitutes a better software engineering practice.

Output of both examples:

    Yellow
    Green
    Blue
    Indigo
    Violet
    Indigo
    Blue
    Green
    Yellow
    Orange
    Red

<aside markdown="1">

---

**Caution!!! Work in progress!!!**

---

    { {extern "manool.org.18/std/0.6/all"} in
    : var { S = {sequence of "Red" "Orange" "Yellow" "Green" "Blue" "Indigo" "Violet"}$ } in
    : var { R = S[RevRange[Size[S]]] } in
    : for { E = S![Range[2; Size[S]]] + R![Range[1; Size[R]]] /*amortized O(1)*/ } do
      Out.WriteLine[E]
    }
^
    { {extern "manool.org.18/std/0.6/all"} in
    : var { S = {sequence of "Red" "Orange" "Yellow" "Green" "Blue" "Indigo" "Violet"}$.Clone[] } in
    : var { R = S[RevRange[Size[S]]] } in
    : for { E = S![Range[2; Size[S]]] + R![Range[1; Size[R]]] /*O(1)*/ } do
      Out.WriteLine[E]
    }

</aside>

### Sets ###############################################################################################################

You can also easily operate with _sets_ and even perform set-theoretic operations using infix operators:

    { {extern "manool.org.18/std/0.6/all"} in
    : for { E = {set of "Red" "Green" "Blue" "Indigo" "Violet"}$ + {set of "Red" "Yellow" "Orange" "Green" "Blue"}$ } do
      Out.WriteLine[E]
    }

Output:

    Blue
    Green
    Indigo
    Orange
    Red
    Violet
    Yellow

Note that the same value cannot occur in a set more than once, and here you cannot have arbitrary control over element ordering anymore (instead, the order of
elements in a set is always implicitly induced by the operation `Order`).

<aside markdown="1">

For any value there always exists at least one group of values (including that value) on which  the operation `Order` induces a total order relation. For
instance:

    { {extern "manool.org.18/std/0.6/all"} in
      Out.WriteLine[Order["abc123"; "abcdef"] ", " Order["abcd"; "abc"] ", " Order["abc"; "abc"]]
    }

Output:

    -1, 1, 0

Strictly speaking, the nature of such ordering is usually unimportant as long as it satisfies the total ordering properties.

</aside>

### Partial updates and iteration over lazily evaluated slices #########################################################

Small, step-wise modifications of composites can be constructed in constant or logarithmic time; slices can be evaluated on-demand (by using first `Elems` to
construct a _view_):

    { {extern "manool.org.18/std/0.6/all"} in
    : var { A = {array of "Red" "Orange" "Yellow" "Green" "Blue" "Indigo"} } in
      /* A = {array of "Violet"}$ + A! /*O(n)*/ */ -- may be slow in case of arrays
      A = A! | "Violet" | "Red" /*amortized O(1)*/ -- append violet and red
      A[5] = "Dark Blue" /*O(1)*/                  -- replace an element; shorthand for:
      /* A = A!.Repl[5; "Dark Blue"] /*O(1)*/ */
    : do Out.WriteLine[A[Size[A] - 1] /*O(1)*/] after     -- output the last elem
    : for { E = A.Elems[Range[Size[A] - 1]] /*O(1)*/ } do -- output all but the last elem
      Out.Write[E; ", "]
    }

Output:

    Red, Orange, Yellow, Green, Blue, Dark Blue, Violet, Red

And now using sequences:

    { {extern "manool.org.18/std/0.6/all"} in
    : var { S = {sequence of "Red" "Orange" "Yellow" "Green" "Blue" "Indigo"} } in
      S = {sequence of "Violet"}$ + S! | "Violet" /*O(1)*/ -- prepend and append violet
      /* A[3] = "Amarillo" /*O(n)*/ */                     -- may be slow in case of sequences
    : do Out.WriteLine[S[Size[S] - 1] /*O(1)*/] after      -- output the last elem
    : for { E = S.Elems[Range[Size[S] - 1]] /*O(1)*/ } do  -- output all but the last elem
      Out.Write[E; ", "]
    }

Output:

    Violet, Red, Orange, Yellow, Green, Blue, Indigo, Violet

And sets:

    { {extern "manool.org.18/std/0.6/all"} in
    : var { S = {set of "Red" "Orange" "Yellow" "Green" "Blue" "Indigo"} } in
      S = S! | "Violet" | "Red" /*O(log n)*/ -- include violet and red (if not present)
      S["Orange"] = False /*O(log n)*/       -- exclude orange (if present); shorthand for:
      /* S = S!.Repl["Orange"; False] /*O(log n)*/ */
    : do Out.WriteLine[S.Elems[][Size[S] - 1] /*O(1)*/] after -- output the last elem
    : for { E = S.Elems[Range[Size[S] - 1]] /*O(1)*/ } do     -- output all but the last elem
      Out.Write[E; ", "]
    }

Output:

    Blue, Green, Indigo, Red, Violet, Yellow


### Nested composites ##################################################################################################

A composite value may contain other composite values as components/elements. Let's construct a funny table or matrix 9 x 7 of color names out of nested arrays:

    { {extern "manool.org.18/std/0.6/all"} in
    : var { Tab = {array 9 of: array 7}$ } in -- 9 x 7 matrix filled with Nil value
      Tab[0] = {array of "Red" "Orange" "Yellow" "Green" "Blue" "Indigo" "Violet"}$
      { for { I = Range[1; Size[Tab]] } do -- Fill out the table
      : for { J = Range[Size[Tab[0]]] } do
        Tab[I; J] = Tab[I - 1; (J - 1).Mod[7]] /*amortized O(1)*/       -- shorthand for:
        /* Tab[I][J] = Tab[I - 1][(J - 1).Mod[7]] /*amortized O(1)*/ */ -- (but faster)
      }
    : for { I = Tab.Keys[] } do -- Print the table
    : for { J = Tab[I].Keys[] } do
      Out.Write[Tab[I; J] /*O(1)*/] -- shorthand for:
      /* Out.Write[Tab[I][J]] */    -- (but faster)
    : if J < Tab[I].Size[] - 1 then
      Out.Write[" "]
      else
      Out.WriteLine[]
    }

  (note that in MANOOL instead of writing `T[I][J]` you can write just `T[I; J]`, which is actually recommended due to performance reasons).

Output:

    Red Orange Yellow Green Blue Indigo Violet
    Violet Red Orange Yellow Green Blue Indigo
    Indigo Violet Red Orange Yellow Green Blue
    Blue Indigo Violet Red Orange Yellow Green
    Green Blue Indigo Violet Red Orange Yellow
    Yellow Green Blue Indigo Violet Red Orange
    Orange Yellow Green Blue Indigo Violet Red
    Red Orange Yellow Green Blue Indigo Violet
    Violet Red Orange Yellow Green Blue Indigo


### Records ############################################################################################################

Records are composite values whose individual components are always identified by keys of type Symbol. A record component is accessible in constant time, but
there are more limitations as to how you can manipulate records (compared to maps).

Let's use records to construct a table of set operations and their descriptions and then iterate over that table:

    { {extern "manool.org.18/std/0.6/all"} in
    : for
      { E =
        { array of
          {record of Description = "Set A"; Op = {proc {A; _} as A}}
          {record of Description = "Set B"; Op = {proc {_; B} as B}}
          {record of Op = (+); Description = "Union"}
          {record of Op = (*); Description = "Intersection"}
          {record of Op = (-); Description = "Difference"}
          {record of Op = (/); Description = "Symmetric difference"}
        }$
      }
      do
    : var
      { S =
        {set of "Red" "Green" "Blue" "Indigo" "Violet"}$.(E[Op] /*O(1)*/)[{set of "Red" "Yellow" "Orange" "Green" "Blue"}$]
      }
      in
      Out.WriteLine["===== " E[Description] /*O(1)*/ ":"]
    : do Out.WriteLine[S.Elems[][Size[S] - 1] /*O(1)*/] after -- last elem
    : for { E = S.Elems[Range[Size[S] - 1]] /*O(1)*/ } do     -- all but the last elem
      Out.Write[E; ", "]
    }

Output:

    ===== Set A:
    Blue, Green, Indigo, Red, Violet
    ===== Set B:
    Blue, Green, Orange, Red, Yellow
    ===== Union:
    Blue, Green, Indigo, Orange, Red, Violet, Yellow
    ===== Intersection:
    Blue, Green, Red
    ===== Difference:
    Indigo, Violet
    ===== Symmetric difference:
    Indigo, Orange, Violet, Yellow


### Maps ###############################################################################################################

Unlike records maps are composite values whose individual elements can be addressed using keys of any type.

Let's construct a dictionary to translate color names from English to Spanish and then another one to translate from English to Portuguese:[^a7]

    { {extern "manool.org.18/std/0.6/all"} in
    : var
      { Es =
        { map of
          "Red"    = "Rojo"
          "Orange" = "Naranja"
          "Yellow" = "Amarillo"
          "Green"  = "Verde"
          "Blue"   = "Azul"
          "Indigo" = "Indigo"
          "Violet" = "Violeta"
        }
      }
      in
    : var { Pt = Es /*O(1)*/ } in            -- make a "virtual" copy (sharing map resources)
      Pt["Red"]    = "Vermelho" /*O(n)*/     -- copy-on-write (automatically unsharing map resources here)
      Pt["Orange"] = "Laranja"  /*O(log n)*/ -- reading and updating of map elements always takes logarithmic time
      Pt["Yellow"] = "Amarelo"  /*O(log n)*/
    : let
      { WriteMap =
        { proc { S; M } as
        : for { K = M.Keys[]; E = M.Elems[] } do -- parallel iteration
          S.WriteLine[K " -> " E]
        }
      }
      in
      Out.WriteLine["=== In Spanish ==="];    Out.WriteMap[Es]
      Out.WriteLine["=== In Portuguese ==="]; Out.WriteMap[Pt]
    }

  (in MANOOL you can iterate over more than one view using more than one loop variable in each step, which is demonstrated above).

[^a7]: This example also demonstrates the non-referential semantics in action.

Output:

    === In Spanish ===
    Blue -> Azul
    Green -> Verde
    Indigo -> Indigo
    Orange -> Naranja
    Red -> Rojo
    Violet -> Violeta
    Yellow -> Amarillo
    === In Portuguese ===
    Blue -> Azul
    Green -> Verde
    Indigo -> Indigo
    Orange -> Laranja
    Red -> Vermelho
    Violet -> Violeta
    Yellow -> Amarelo


* * * * *
**[Continue](lesson-5 "Next Lesson")**
<aside markdown="1" class="right">
Lesson 4 of 5 -- Tutorial
=========================
+ [Lesson 1](lesson-1#start)
+ [Lesson 2](lesson-2#start)
+ **[Previous Lesson](lesson-3#start)**
+ **[Next Lesson](lesson-5#start)**
</aside>

{%endraw%}{%include page_footer.md%}
