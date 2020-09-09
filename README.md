# translation-tool-quest
Not at all a test to see if I can make a translation tool in C++

Notes to users:
1. Currently you need to have the /src and /dst-core directories in the same directory as the executable
2. The output JSON is malformed. This is because I am constructing it in a disgusting manual fashion,
and am left with a trailing ',' after the last entry.
3. I'm not sure yet that I'm catching all matches, because my output map file has less lines than the src file..
This is probably because I'm not doing anything clever whatsoever at the moment regarding pattern matching my strings.