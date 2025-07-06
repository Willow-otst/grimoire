# Grimoire
 - Basically a personal Wiki / Note-taking app for my home table-top games.
 - Searchable like a Wiki.

## The Idea:
- I play a lot of table-top (mainly just home-brew D&D) and normally i use Google Drive for my Note-Takeing, but it is not very searchable.
- I want a tool that can host my notes but also be searchable like a wiki. I know tools exist for this, but i thought this would be fun, and this way i can expand on the idea with plugins and stuff in the future.
  
## The Stack:
- C++ Because its Cross-Plat and Statically Typed.
- wxWidgets for UI. (See LOG 2.)
- SQLite + FTS5 for Saving Notes and Search Functionality.
- Markdown/XML/JSON for Saving/Loading notes.

## The Features:
### MVP:
- Live "WYSIWYG" Rich Text Editor (headers, bold, indents etc..).
	- "WYSIWYG" = "What You See Is What You Get"
- Saving Notes in the DB
- Loading Notes from the DB
- Searching Notes in the DB (Using FTS5)
- Autosave for notes.
- Cross-platform deployment (Linux/Windows)

### Extras:
- Jump-Links to and between notes.
- Collapsable Headers/Bulleted Lists
- Saving / Loading Note History (Likly in a seperate DB)
- Archival Search (searching note history)
- Multi-Tab & Multi-Window Support (Like a web Browser)
- Dark mode / Theme Support
- Exporting Notes (to .txt, .pdf, .md, etc..)
- Importing Notes (from .txt, .md, .docx, etc...)

### Wishlist:
- Custom Plugin Support for extra tools like a built-in character sheet manager. (Think D&D beyond but 100% homebrew)

## Log
1. Migrated from QT to FLTK
	* QT Was too high-level and offered little in terms of custom tooling.
	* Moved to FLTK for more Direct Control over the codebase and app functionality.
2. Migrated from FLTK to wxWidgets
	* Moved to wx for out of the box rich text support.
	* FLTK was Awesome to work with, it was really easy to get going and would have been quite maintainable.
	* Honestly if not for that, I would have kept using it and will probably use it in the future for simpler projects.
	* wxWidgets should offer a nice middle ground between the complexity of Qt and FLTK's Lack of hand holding.
