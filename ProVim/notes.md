<div align="center"> 
    <h1> Pro Vim 3rd Edition</h1>  
 <p> <i> Mark McDonnell</i> </p>

</div><div align="center">
    <img src="./images/capa.png" width="600px">
</div>

## Chapter 4 - Files
    - Using the '!' character, allow shell script to be executed while Vim is running in the background.
        - *e.g: ':!ls'*
## Commands
### Helpers
    - ':e {Space} {Ctrl-d}': List all files in the current directory.
### Cursor
    - 'gg': Move cursor to first line.
    - '5gg': Move cursor to 5th line.
    - 'G': Move cursor to last line.
    - '$': Move cursor to the end of line.
    - '^^': Move cursor to the start of line.
    - 'A': Move cursor to the end of line and switch to INSERT mode.
    - 'I': Move cursor to the start of line and switch to INSERT mode.
### Changes
    - 'u': Undo
    - 'Ctrl+y': Redo
### Files
    - ':10read': Read a file and place its content in the 10th line of the current buffer.
    - 'ctrl+w n' or ':new': Create a new buffer splitted horizontally.
    - 'vnew': Create a new buffer splitted vertically.
    - 'tabnew': Create a new buffer inside a new tab.  
    -    
