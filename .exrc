if &cp | set nocp | endif
let s:cpo_save=&cpo
set cpo&vim
imap <F12> :Exi
imap <F11> :TlistToggle
imap <F10> :bd
imap <F9> :makei
imap <F8> :MarksBrowser
imap <F7> :bni
imap <F6> :bpi
imap <F5> :BufExplorer
imap <F2> :wi
vmap  "+yi
map  :qa
nmap   <PageDown>
noremap <silent> ,oh :AS  
noremap <silent> ,ov :AV  
noremap <silent> ,o :A  
noremap <silent> ,9 :BufExplorerVerticalSplit  
noremap <silent> ,8 :resize -10
noremap <silent> ,7 :resize +10
noremap <silent> ,6 :vertical resize +10
noremap <silent> ,5 :vertical resize -10
noremap <silent> ,4 :TlistClose 
noremap <silent> ,3 :Tlist  
noremap <silent> ,2 :NERDTreeClose 
noremap <silent> ,1 :NERDTree  
nmap ; :%s/\<=expand("<cword>")\>/
vmap < <gv
vmap > >gv
nmap gx <Plug>NetrwBrowseX
nnoremap <silent> <Plug>NetrwBrowseX :call netrw#NetrwBrowseX(expand("<cWORD>"),0)
vmap <F12> :Exi
vmap <F11> :TlistToggle
nmap <F11> :TlistToggle
omap <F11> :TlistToggle
vmap <F10> :bd
nmap <F10> :bd
omap <F10> :bd
vmap <F9> :makei
nmap <F9> :make
omap <F9> :make
vmap <F8> :MarksBrowser
nmap <F8> :MarksBrowser
omap <F8> :MarksBrowser
vmap <F7> :bni
nmap <F7> :bn
omap <F7> :bn
vmap <F6> :bpi
nmap <F6> :bp
omap <F6> :bp
vmap <F5> :BufExplorer
nmap <F5> :BufExplorer
vmap <F2> :wi
nmap <F2> :w
map <S-Insert> <MiddleMouse>
map <F3> :call TRANSLATE() 
nmap <F12> :Ex
omap <F12> :Ex
imap  
imap 	 =InsertTabWrapper()
imap  "+gPi
imap >Ins> i
imap [ []<Left>
imap { {}O
let &cpo=s:cpo_save
unlet s:cpo_save
set autoindent
set background=dark
set backspace=indent,eol,start
set comments=sl:/*,mb:\ *,elx:\ */
set complete=.,k,b,t
set expandtab
set fileencodings=utf-8,cp1251
set formatoptions=tqcr
set helplang=en
set hidden
set hlsearch
set ignorecase
set incsearch
set mouse=a
set mousemodel=popup
set printoptions=paper:a4
set ruler
set runtimepath=~/.vim,/var/lib/vim/addons,/usr/share/vim/vimfiles,/usr/share/vim/vim73,/usr/share/vim/vimfiles/after,/var/lib/vim/addons/after,~/.vim/after
set scrolljump=7
set scrolloff=7
set shiftwidth=4
set showcmd
set showmatch
set smartcase
set smartindent
set softtabstop=4
set suffixes=.bak,~,.swp,.o,.info,.aux,.log,.dvi,.bbl,.blg,.brf,.cb,.ind,.idx,.ilg,.inx,.out,.toc
set tabstop=4
set termencoding=utf-8
set textwidth=120
set whichwrap=b,s,<,>,[,]
set wildcharm=<Tab>
set wildmenu
" vim: set ft=vim :
