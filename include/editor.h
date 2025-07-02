#include <FL/Fl_Double_Window.H>

class EditorWindow {
private:
    Fl_Double_Window *mainWindow;
public:
    EditorWindow(); // Constuctor
    int Start(int argc, char **argv);
    // Text Menu
    static void Text_Bold(Fl_Widget *, void *);
    static void Text_Italic(Fl_Widget *, void *);
    static void Text_Strikethrough(Fl_Widget *, void *);

};
