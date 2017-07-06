#include "dlist.h"
#include "utility.h"

using namespace std;

void Task(DList &input)
{
    cout << "The line terminator is '.'" << endl;
    QString buffer;
    QTextStream IN(stdin);
    int max = numeric_limits<int>::min();
    do
    {
        IN >> buffer;
        if (buffer == '.')
            break;
        else
            if (input.is_empty())   // if input number is first
            {
                input.push_front(buffer.toInt());
                max = buffer.toInt();
            }
            else
                if (input.find(buffer.toInt()) == input.end())   // preventing of duplicating
                {
                    if (buffer.toInt() > max)             // pushing back the largest number
                    {
                        max = buffer.toInt();
                        input.push_back(buffer.toInt());
                    }
                    else
                        // if number will be in the middle of the list
                        input.insert_before(input.findFEGG(buffer.toInt()), buffer.toInt());
                }

    }
    while (buffer != '.');

    if (input.is_empty())
        throw std::runtime_error("List is empty");
    else
        cout << input;
}
