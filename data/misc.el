;;; misc.el --- Miscellaneous functions for Vaucanson development.
;;
;; Copyright (C) 2006 The Vaucanson Group

;; Author: Michael Cadilhac <michael.cadilhac@lrde.org>
;; Keywords: Vaucanson, indentation.

;; This file is part of Vaucanson, a generic library for finite state
;; machines.

;; This is free software; you can redistribute it and/or modify it
;; under the terms of the GNU General Public License as published by
;; the Free Software Foundation; either version 2, or (at your option)
;; any later version.

;; The complete GNU General Public Licence Notice can be found as the
;; `COPYING' file in the root directory.

;;; Commentary:

;; These functions are to be used by Vaucanson developers in the hope
;; it will help uniformize the use of some part of the project's
;; coding style.

;; If you want to use Vaucanson indentation, add the following to your
;; .emacs (init.el):
;; (setq c-default-style "Vaucanson")

;;; Code:

;; This is the indentation mode for Vaucanson:

(require 'cc-mode)

;; Add indentation style
(unless (assoc "Vaucanson" c-style-alist)
  (add-to-list
   'c-style-alist
   '("Vaucanson"
     (c-basic-offset	       . 2)
     (c-comment-only-line-offset . 0)
     (c-hanging-braces-alist     . ((substatement-open before after)))
     (c-offsets-alist
      . ((topmost-intro          . 0)
	 ;; Align if starts with *
	 (c . (lambda (of)
		(save-excursion
		  (forward-line 0)
		  (if (looking-at "[[:space:]]*[|`]") 0 3))))
	 ;; /*- comments stay in place.
	 (comment-intro . (lambda (of)
			    (save-excursion
			      (forward-line 0)
			      (skip-chars-forward "[:space:]" (point-at-eol))
			      (when (looking-at "/\\*-")
				(vector (current-column))))))
	 (substatement         . +)
	 (substatement-open    . 0)
	 (case-label           . +)
	 (access-label         . -)
	 (inclass              . ++)
	 (inline-open          . 0))))))


;; Indentation of cpp macros.

(defun cpp-indent-macros (beg end)
  "Adjust the use of space after # between BEG and END."
  (interactive "r")
  (save-excursion
    (save-restriction
      (let ((spaces 0))
	(goto-char beg)
	(when (re-search-backward "^[[:space:]]*#\\([[:space:]]*\\)[a-z]" nil t)
	  (setq spaces (- (match-end 1) (match-beginning 1))))
        (narrow-to-region beg end)
	(while (re-search-forward "^[[:space:]]*#\\([[:space:]]*\\)\\([a-z]\\{,5\\}\\)" nil t)
	  (and (or (string= "endif" (match-string 2))
		   (string= "el" (substring (match-string 2) 0 2))) (> spaces 0)
	       (decf spaces))
	  (unless (= (- (match-end 1) (match-beginning 1)) spaces)
	    (replace-match (make-string spaces ? ) nil nil nil 1))
	  (when (string= "el" (substring (match-string 2) 0 2))
	    (incf spaces))
	  (when (string-match "^if" (match-string 2)) (incf spaces)))))))

;; Vaucansonize a buffer.

(require 'tabify)

(defun vaucansonize-buffer (&optional buffer)
  "Change BUFFER to follow some Vaucanson coding style rules."
  (interactive)
  (unless buffer
    (setq buffer (current-buffer)))
  (with-current-buffer buffer
    (let ((c-indentation-style "Vaucanson"))
      (barf-if-buffer-read-only)
      (indent-region (point-min) (point-max))
      (cpp-indent-macros (point-min) (point-max))
      (delete-trailing-whitespace)
      (tabify (point-min) (point-max)))))


;; arch-tag: 97e769b8-ed42-42d9-bac6-7833bea581c5
;;; misc.el ends here
