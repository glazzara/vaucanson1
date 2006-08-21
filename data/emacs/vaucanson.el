;;; vaucanson.el --- Miscellaneous functions for Vaucanson development.
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

;; To use M-x vaucansonize-buffer RET, just add (require 'vaucanson).

;;; Code:

(require 'cc-mode)
;; Rebox doesn't `provide' itself usually.
(unless (or (ignore-errors (require 'rebox))
	    (ignore-errors (load "rebox.el")))
  (with-temp-message "Warning: `rebox.el' not found"
    (sleep-for 2)))

(defcustom c-header-file-extensions
  "\\(hh\\|hxx\\|hcc\\|thh\\|thxx\\)\\(\\.in\\)?"
  "File extensions regexp for C(++) header files."
  :group 'c)

(defvar cpp-guard-prefix ""
  "Prefix for CPP guard, e.g. `VCSN_'.")

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
		  (if (looking-at "[[:space:]]*[|`]") 0 1))))
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
		   (string= "el" (substring (match-string 2) 0 2)))
	       (> spaces 0)
	       (setq spaces (1- spaces)))
	  (unless (= (- (match-end 1) (match-beginning 1)) spaces)
	    (replace-match (make-string spaces ? ) nil nil nil 1))
	  (when (string= "el" (substring (match-string 2) 0 2))
	    (setq spaces (1+ spaces)))
	  (when (string-match "^if" (match-string 2)) (setq spaces (1+ spaces))))))))


;; Get Vaucanson relative path.
(defun get-vcsn-path (&optional path)
  "Get Vaucanson relative path for PATH."
  (unless path
    (setq path buffer-file-name))
  (unless path
    (error "No path provided and `buffer-file-name' nil"))
  (let ((vcsn-start (string-match "include/vaucanson/" path)))
    (if vcsn-start
	(substring path (match-end 0))
      (file-name-nondirectory path))))


;; Verify the form of the guard.
(defun cpp-check-guard (&optional file-name-to-useful-part)
  "Verify that the CPP guard is rightly made in the current buffer.
The function uses `file-name-to-useful-part' (`file-name-nondirectory'
if nil) to get the part of the filename that should be part of the
macro gard.  The check is made if and only if the current file name
matches `c-header-file-extensions'.  CPP should be correctly indented."
  (interactive)
  (unless file-name-to-useful-part
    (setq file-name-to-useful-part 'file-name-nondirectory))
  (unless buffer-file-name
    (error "Current buffer doesn't have any associated file"))
  (when (string-match (concat c-header-file-extensions "$")
		      buffer-file-name)
    (let ((old-point (point))
	  (expected-guard
	   (concat cpp-guard-prefix
		   (replace-regexp-in-string
		    "[./]" "_"
		    (upcase (funcall file-name-to-useful-part buffer-file-name))))))
      (goto-char (point-min))
      (unless (re-search-forward "^#if" nil t)
	(error "Guard start not found"))
      (unless (looking-at (concat "ndef[[:space:]]+" (regexp-quote expected-guard)))
	(error "Expecting `#ifndef %s'" expected-guard))
      (beginning-of-line 2)
      (unless (looking-at (concat "# define[[:space:]]+"
				  (regexp-quote expected-guard)))
	(error "Expecting a definition of `%s'" expected-guard))
      (unless (re-search-forward "^#endif" nil t)
	(error "Guard end not found"))

      (unless (search-forward expected-guard (point-at-eol) t)
	(error "Comment `#endif' should mention `%s'" expected-guard))
      (goto-char old-point)
      nil)))

(defun doxymacs-check-group-consistency (beg end)
  "Check if @{ and @} are rightly organized between BEG and END."
  (interactive "r")
  (let ((groups nil)
	(old-point (point)))
    (goto-char beg)
    (while (re-search-forward "@{\\|@}" end t)
      (let (is-comment)
	(when (dolist (syntax (c-guess-basic-syntax) is-comment)
		(setq is-comment (or is-comment
				     (memq (car syntax) '(c comment-intro)))))
	  (if (eq (char-before) ?{)
	      (push (point) groups)
	    (unless (pop groups)
	      (error "Too much @} here"))))))
    (unless (null groups)
      (goto-char (car (last groups)))
      (error "There is %d doxygen opening (@{) not closed, point at first one"
	     (length groups)))
    (goto-char old-point)))


(require 'tabify)
(require 'whitespace)

;; Vaucansonize a buffer.
(defun vaucansonize-buffer (&optional buffer)
  "Change BUFFER to follow some Vaucanson coding style rules."
  (interactive)
  (unless buffer
    (setq buffer (current-buffer)))
  (with-current-buffer buffer
    (let (c-indentation-style)
      (c-set-style "Vaucanson")
      (barf-if-buffer-read-only)
      (cpp-indent-macros (point-min) (point-max))
      (indent-region (point-min) (point-max) nil)
      (let ((whitespace-check-buffer-leading t) (whitespace-check-buffer-trailing t)
	    (whitespace-check-buffer-indent t) (whitespace-check-buffer-spacetab t)
	    (whitespace-check-buffer-ateol t) (whitespace-highlighted-space t)
	    (whitespace-silent t))
	(whitespace-cleanup))
      (tabify (point-min) (point-max))
      (when (and buffer-file-name
		 (string-match "include/vaucanson/" buffer-file-name))
	(let ((cpp-guard-prefix "VCSN_"))
	  (cpp-check-guard 'get-vcsn-path)))
      (doxymacs-check-group-consistency (point-min) (point-max)))
    (c-set-style c-indentation-style)))


;; For fun ;-)
(provide 'vaucanson)

;; arch-tag: 97e769b8-ed42-42d9-bac6-7833bea581c5
;;; vaucanson.el ends here
