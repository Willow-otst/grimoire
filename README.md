# Grimoire
 - Basically a personal Wiki / Note-taking app for my home table-top games.
 - Searchable like a Wiki.

## The Idea:
- I play a lot of table-top (just hmoe-brew D&D) and normally i use Google Drive for my Note-Taking, but it is not very searchable.
- I want a tool that can host my notes but also be searchable like a wiki. I know tools exist for this, but i thought this would be fun, this way i can expand on the idea with plugins and stuff in the future.
 
## The Audience:
- Me. (Nothing revolutionary.)
  
## The Stack:
- C++ Because its Cross-Plat and Statically Typed. (I dont care for Java.)
	- Also i get to learn more C++.
- FLTK/FLUID for UI. (See LOG 1.)
- SQLite + FTS5 for Saving Notes and Search Functionality.
- Markdown for Saving/Loading notes.
- JSON for Meta-Data and support in the Database. (SQL is a Headache)

## The Features:
### MVP:
- Live Markdown/Rich Text Editor (This means full markdown support, think headers, bold, indents etc..)
- "WYSIWYG" Loaded into the Editor, the markdown stuff is handeld on the backend.
	- "WYSIWYG" = "What You See Is What You Get"
- Saving Notes in the DB (as Markdown/JSON)
- Loading Notes from the DB (from Markdown/JSON)
- Searching Notes in the DB (Using FTS5)
- Autosave for notes. (Like cloud editors, thing google drive.)
- Cross-plat deployment (Linux/Windows)

### Extras:
- Jump-Links to and between notes.
- Collapsable Headers/Bulleted Lists
- Multiple 
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
