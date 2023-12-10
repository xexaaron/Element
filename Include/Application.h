#ifndef APPLICATION_H
#define APPLICATION_H

class Application final {
public:
    static void Initialize();

private:
    static bool IsRunning;

};

#endif // APPLICATION_H