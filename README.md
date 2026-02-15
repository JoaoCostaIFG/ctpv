# ctpv

File previewer for a terminal

![showcase](doc/showcase.gif)

----

ctpv is a file previewer utility for a terminal.

It was made with integration into [lf file manager][lf] in mind,
but I believe that it can be easily integrated into other programs
as well.

It supports previews for source code, archives, PDF files, images,
videos, etc.
See [Previews](#previews) for more info.

Image previews are powered by one of these programs:

* [Chafa][chafa]
* [Kitty image protocol][kitty]

**This is an actively maintained fork** of the original ctpv project.
It aims to stay up-to-date with the latest [lf][lf] releases, fix bugs,
add new previewers, and improve existing ones.

ctpv is a remake of an awesome program named
[stpv](https://github.com/Naheel-Azawy/stpv).
stpv did everything I wanted, except it was a bit sluggish because
it was written in POSIX shell.
ctpv is written in C and is an attempt to make a faster version of
stpv with a few new features.

## Previews

Previewing each file type requires specific programs installed on
a system.
If a program is not found on the system, ctpv
will try to use another one.
Only one program is required for each file type.
For example, you only need either `elinks`, `lynx` or
`w3m` installed on your system to view HTML files.

<!-- This table is auto generated! -->
<!--TABLESTART-->
| File types | Programs |
| ---- | ---- |
| 3d | f3d |
| any | [exiftool][exiftool] cat |
| archive | [atool][atool] ouch |
| audio | [ffmpegthumbnailer][ffmpegthumbnailer] [ffmpeg][ffmpeg] |
| diff | [colordiff][colordiff] [delta][delta] [diff-so-fancy][diff-so-fancy] |
| directory | ls |
| epub | pandoc |
| font | magick |
| gpg-encrypted | [gpg][gpg] |
| html | [elinks][elinks] [lynx][lynx] [w3m][w3m] |
| image | [chafa][chafa] |
| iso | isoinfo 7z |
| json | [jq][jq] |
| jupyter | jupyter nbconvert [jq][jq] |
| markdown | [glow][glow] [mdcat][mdcat] |
| office | [libreoffice][libreoffice] |
| pdf | pdftoppm |
| sqlite | sqlite3 |
| svg | magick |
| text | bat cat [highlight][highlight] [source-highlight][source-highlight] |
| torrent | transmission-show |
| video | [ffmpegthumbnailer][ffmpegthumbnailer] |
| webp | magick |

[ffmpegthumbnailer]: https://github.com/dirkvdb/ffmpegthumbnailer
[w3m]: https://w3m.sourceforge.net/
[elinks]: http://elinks.cz/
[exiftool]: https://github.com/exiftool/exiftool
[highlight]: https://gitlab.com/saalen/highlight
[chafa]: https://github.com/hpjansson/chafa
[gpg]: https://www.gnupg.org/
[delta]: https://github.com/dandavison/delta
[colordiff]: https://www.colordiff.org/
[source-highlight]: https://www.gnu.org/software/src-highlite/
[mdcat]: https://github.com/swsnr/mdcat
[glow]: https://github.com/charmbracelet/glow
[atool]: https://www.nongnu.org/atool/
[lynx]: https://github.com/jpanther/lynx
[libreoffice]: https://www.libreoffice.org/
[diff-so-fancy]: https://github.com/so-fancy/diff-so-fancy
[jq]: https://github.com/jqlang/jq
[ffmpeg]: https://ffmpeg.org/

<!--TABLEEND-->

**Note:** While `bat` is optional, it is highly recommended for optimal text
previews. When installed, `bat` is used to wrap text output from many other
previewers to ensure proper line width limiting, preventing text overflow in
the preview window. Without `bat`, text from tools like `cat`, `jq`,
`colordiff`, and others may extend beyond the window width.

## Installation

### Manual

If you are building from source, make sure to install these libraries!
Depending on your system, you probably will also need "devel" versions
of the same libraries.

* `libcrypto`
* `libmagic`

Install:

```bash
git clone https://github.com/NikitaIvanovV/ctpv
cd ctpv
make
sudo make install
```

Uninstall:

```bash
sudo make uninstall
```

### AUR

If you are an Arch Linux user, you can install the [PKGBUILD](./PKGBUILD)
file in this repo.

```bash
makepkg -si
```

## Integration

### lf file manager

Add these lines to your lf config (usually located at `~/.config/lf/lfrc`).

```bash
set previewer ctpv
set cleaner ctpvclear
cmd on-quit &{{
  ctpvquit
}}
```

### Image previews

ctpv supports multiple methods for displaying image previews, depending on your terminal and installed tools:

**Kitty image protocol** (recommended)
If your terminal supports it (e.g., Kitty, Ghostty), ctpv will automatically use the Kitty image protocol for native image rendering.

**Sixel support**
For terminals that support Sixel graphics with Chafa, enable sixel output by adding the following to `~/.config/ctpv/config`:

```
set chafasixel
```

**Fallback**
If neither of the above options are available, ctpv will use Chafa's lower-resolution Unicode/ANSI character-based previews.

## Documentation

Full documentation on command line options,
configuration and how to define custom previews can be in the
man page:

```bash
man ctpv
```

[kitty]: https://github.com/kovidgoyal/kitty
[lf]: https://github.com/gokcehan/lf
