# Header Only String & Array

This is a header only C++ library that is supposed to be very easy to use. It's not meant to be the fastest, most optimized library out there, its only focus is to be both easy to use and easy to get working in your project. It's not targeted at professional users, but at beginners, to make interacting with the console and formatting strings easier and more expressive.

---
## Using Hosa
To use Hosa in your project, the only things you need to do is:

* clone/download this repository
* move it into your project folder
* ```#include "hosa/hosa.h"```
* make sure you're using C++17 or newer

That's all, you should now be able to use it. 

---
## Why Hosa?
Hosa is mainly targeted at programmers with very little C++ experience. Many patterns that are used in Python or JavaScript have been put into this library to make tinkering very easy.

For example, if you quickly want a formatted string that you can print to the console, this is how it's done with Hosa:

```cpp
#include "hosa/hosa.h"

// this enables the use of the _s suffix to turn a C-string into a hosa::String
using namespace hosa;

int main()
{
    "{} is very {} to use."_s.format ("Hosa", "easy").print();

    return 0;
}
``` 
---
This formatting works with all primitive types and the String class itself. In the future it should be compatible with all iostreamable types.

Notice how we can simply put _s after a C-string and make it a hosa::String. This only works if you put ```using namespace hosa;``` in your code. If you only need the _s suffix and want to be explicit about the rest, you can also use ```using namespace hosa::literals;```

Features like swapping words, replacing text, getting the index of a substring, converting the whole string to upper or lower case, or simply reversing the string are all very simple with hosa::String:

```cpp
#include "hosa/hosa.h"

// now we can use _s, but still need to be explicit about hosa::String..
using namespace hosa::literals;

int main()
{
    "dogs are better than cats"_s.swap ("dogs", "cats").print();

    "!gnizama si asoH"_s.reverse().print();

    if ("1234"_s.indexOfSubString ("3") == 2)
        "It contains 3!"_s.print();
    
    "Hosa is hard"_s.replace ("hard", "easy"_s.toUpperCase()).print();

    return 0;
}
```

---
Of course hosa::String and hosa::Array work very well together as well:

```cpp
#include "hosa/hosa.h"

using namespace hosa;

int main()
{
    auto numbers = "one, two, three, four"_s;

    auto clipOffWhitespace = true;

    auto numArray = numbers.split (","_s, clipOffWhitespace);

    for (auto& n : numArray)
        n.print();

    // this also works the other way around
    auto lispList = "({})"_s.format (String::joinFromArray (numArray, " "_s));

    lispList.print();

    // a hosa::String can also be easily turned into a std::string
    auto s = lispList.toStdString();

    // getting date and time as a string is also very easy
    "Now is: {}"_s.format (String::getDateAndTime()).print();

    return 0;
}
``` 
---
If, for some reason, you want to build the tests, you can do that with the following steps (CMake is required):

```bash
mkdir build
cd build
cmake ../tests
cmake --build .
```


---
As mentioned, hosa is not meant for professional use. There are better alternatives, although they're a bit harder to setup and use in your project. 
The juce::String class is an amazing class to use in bigger projects and libfmt is probably the best for printing formatted text to the console. But both are more of a hassle to get into your project.

Any suggestions to make Hosa better are always welcome.