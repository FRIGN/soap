/* See LICENSE file for copyright and license details. */

static const Pair pairs[] = {
	/* regex                  action */
	{ "\.(jpg|png|tiff)$",    "feh %s"        },
	{ "\.gif$",               "wget -O /tmp/tmp_gifview.gif %s && gifview -a /tmp/tmp_gifview.gif" },
	{ "\.mp3$",               "st -e mplayer %s" },
	{ "^(http://|https://)?(www\.)?(youtube.com/watch\?|youtu\.be/)", "youtube-viewer %s" }
};
