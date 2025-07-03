#pragma once
/* =============================================================
===  Custom FLTK Text-Box Implementation.                    ===
===  Inherets FLTK Fl_Text_Editor to create a Rich-Text-Box  ===
============================================================= */

class G_TextBox : public Fl_Text_Editor {
private:
protected:
    void draw() override;
public:
    G_TextBox(int x, int y, int w, int h, const char *label = nullptr);

};
