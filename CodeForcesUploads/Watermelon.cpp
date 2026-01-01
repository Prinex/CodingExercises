#include <iostream>
#include <string>

std::string Watermelon(int w)
{
    if (w <= 2) return "NO";
    for (int i = 2; i < w + 1; i++)
    {
        if (i % 2 == 0 && ((w - i) % 2) == 0)
        {
	    return "YES";
    	}
    }
    return "NO";
}

int main()
{
    int outputInteger;
    std::cin >> outputInteger;
    std::string o = Watermelon(outputInteger);
    std::cout << o << std::endl;

    return 0;
}

/*
int main(int argc, char** argv)
{
    int outputInteger = atoi(argv[1]);

    std::string o = Watermelon(outputInteger);
    std::cout << o << std::endl;

    return 0;
}*/
