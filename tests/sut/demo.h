#ifndef _DEMO_H_
#define _DEMO_H_

namespace Foo
{
	class Turtle
	{
	public:
		virtual int GetX() { return 1; }
		virtual int GetY() { return 2; }
		virtual void Turn(int degrees) {};
		virtual bool GoTo(int x, int y) 
		{
			return false;
		}
    protected:
        void Run() {}
    private:
        void Walk() {}
	};

	bool Download(const char* url)
	{
		return false;
	}
}

bool Connect(const char* ip)
{
    return false;
}

class Dog
{
public:
    int GetAge()
    {
        return 2;
    }

    static int GetCount()
    {
        int result = 10;
        // ...
        return result;
    }
};

#endif


