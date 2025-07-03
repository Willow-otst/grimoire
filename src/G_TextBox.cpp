/* =============================================================
===  Custom FLTK Text-Box Implementation.                    ===
===  Inherets FLTK Fl_Text_Editor to create a Rich-Text-Box  ===
============================================================= */

#include <FL/Fl_Text_Editor.H>
#include "G_TextBox.h"

G_TextBox::G_TextBox(int x, int y, int w, int h, const char *label) : Fl_Text_Editor(x, y, w, h, label) {

}
void G_TextBox::draw() {
    Fl_Text_Editor::draw();
}
