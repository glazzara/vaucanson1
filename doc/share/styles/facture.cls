%%% facture.cls --- Classe LaTeX pour les factures LRDE

%% Copyright (C) 2002, 2006 Didier Verna.

%% PRCS: $Id: facture.cls 1.2 Wed, 25 Sep 2002 10:09:54 +0200 didier $

%% Author:        Didier Verna <didier@lrde.epita.fr>
%% Maintainer:    Didier Verna <didier@lrde.epita.fr>
%% Created:       Tue Sep 24 16:14:34 2002 under XEmacs 21.5 (beta 5)
%% Last Revision: Tue Sep 24 16:14:34 2002

%% This program may be distributed and/or modified under the
%% conditions of the LaTeX Project Public License, either version 1.1
%% of this license or (at your option) any later version.
%% The latest version of this license is in 
%% http://www.latex-project.org/lppl.txt
%% and version 1.1 or later is part of all distributions of LaTeX
%% version 1999/06/01 or later.

\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{facture}[2006/03/02 v1.0 Bill Class for LRDE]

\def\@header{{\LARGE Association EPITA}}
\def\@footer{%
  {\small
    Association EPITA -- Association Loi 1901 -- SIRET n$^{\mbox{\tiny o}}$
    443 220 223 00012 code APE 803 Z}}
\DeclareOption{epita}{}
\DeclareOption{transfia}{
  \def\@header{{\LARGE TRANSFIA}\\c/o EPITA}
  \def\@footer{%
    {\small
      TRANSFIA -- Association Loi 1901 -- SIRET n$^{\mbox{\tiny o}}$
      401 872 684 00014}}}

\ProcessOptions

\LoadClass[10pt]{letter}
\RequirePackage[a4paper,nohead,nofoot,hmargin=1.5cm,vmargin=1.5cm]{geometry}
\RequirePackage[francais]{babel}
\RequirePackage[latin1]{inputenc}
\RequirePackage[T1]{fontenc}
\RequirePackage{palatino}
\RequirePackage{tabularx}
\RequirePackage{pifont}
\RequirePackage{eurosym}

\def\@numero{%
  \ClassError{Facture}{Il manque le numero de facture}{%
    Vous devez appeler la commande \protect\numero\space dans le preambule
    du document.\MessageBreak}}
\newcommand\numero[1]{\gdef\@numero{#1}}
\@onlypreamble\numero

\def\@kind{%
  \ClassError{Facture}{Il manque la nature du document (facture ou devis)}{%
    Vous devez appeler la commande \protect\kind\space dans le preambule
    du document.\MessageBreak}}
\newcommand\kind[1]{\gdef\@kind{#1}}
\@onlypreamble\kind

\def\@nom{%
  \ClassError{Facture}{Il manque le nom de la societe}{%
    Vous devez appeler la commande \protect\nom\space dans le preambule
    du document.\MessageBreak}}
\newcommand\nom[1]{\gdef\@nom{#1}}
\@onlypreamble\nom

\def\@adresse{%
  \ClassError{Facture}{Il manque l'adresse}{%
    Vous devez appeler la commande \protect\adresse\space dans le preambule
    du document.\MessageBreak}}
\newcommand\adresse[1]{\gdef\@adresse{#1}}
\@onlypreamble\adresse

\def\@responsable{%
  \ClassError{Facture}{Il manque le nom du responsable}{%
    Vous devez appeler la commande \protect\responsable\space dans le preambule
    du document.\MessageBreak}}
\newcommand\responsable[1]{\gdef\@responsable{#1}}
\@onlypreamble\responsable

\def\@telephone{%
  \ClassError{Facture}{Il manque le numero de telephone du responsable}{%
    Vous devez appeler la commande \protect\telephone\space dans le preambule
    du document.\MessageBreak}}
\renewcommand\telephone[1]{\gdef\@telephone{#1}}
\@onlypreamble\telephone

\def\@reference{%
  \ClassError{Facture}{Il manque la reference de la facture}{%
    Vous devez appeler la commande \protect\reference\space dans le preambule
    du document.\MessageBreak}}
\newcommand\reference[1]{\gdef\@reference{#1}}
\@onlypreamble\reference

\newenvironment{liste}{%
  \tabularx{\textwidth}{|c|c|X|c|r|r|}
  \hline
  \textbf{R�f�rence} & \textbf{Quantit�} & \textbf{Description} &
  \textbf{Code T.V.A.} & \textbf{P.U. (\euro)} & \textbf{Montant (\euro)}\\
  \hline}{%
  \endtabularx}

%% <ref>, <qt�>, <descr>, <code>, <pu>, <montant>
\newcommand\element[6]{#1&#2&#3&#4&#5&#6\\}

\newcommand\espace[1]{&&~\vspace{#1}&&&\\\hline}

\newcommand\totalht[1]{%
  \multicolumn{3}{l}{}&\multicolumn{2}{|r|}{Total H.T.}&#1\\
  \cline{4-6}}

\newcommand\tva[2]{%
  \multicolumn{3}{l}{}&\multicolumn{2}{|r|}{T.V.A.: #1}&\gdef\@tva{#2}\@tva\\
  \cline{4-6}}

\newcommand\totalttc[1]{%
  \multicolumn{3}{l}{} &
  \multicolumn{2}{|r|}{\textbf{Total T.T.C.}}&#1\\
  \cline{4-6}
  \multicolumn{3}{l}{} &
  \multicolumn{2}{|r|}{\textbf{Dont T.V.A.}}&\@tva\\
  \cline{4-6}}

\AtBeginDocument{%
  \begin{minipage}{.5\textwidth}
    \@header\\
    14/16 rue Voltaire\\
    94276 Le Kremlin-Bic�tre CEDEX\\
    France\\
    \\
    T�l�phone: 01 53 14 59 47\\
    T�l�copie: 01 53 14 59 22
  \end{minipage}
  \hfill
  \begin{minipage}{.385\textwidth}
    {\LARGE\bfseries \@kind} n$^{o}$ \@numero
  \end{minipage}
  \thispagestyle{empty}

  \rule{\textwidth}{1mm}

  \vspace{5mm}

  \begin{minipage}{.6\textwidth}
    \begin{tabular}{@{}lp{\textwidth}@{}}
      Nom:&\@nom\\
      Adresse:&\@adresse\\
      Responsable:&\@responsable\\
      T�l�phone:&\@telephone
    \end{tabular}
  \end{minipage}
  \hfill
  \begin{minipage}{.4\textwidth}
    \begin{tabular}{@{}ll@{}}
      Date:&\@date\\
      R�f. Commande:&\@reference
    \end{tabular}
  \end{minipage}

  \vspace{1cm}}

\AtEndDocument{%
  \vfill

  \fbox{\parbox[l][4cm]{.45\textwidth}{%
      \textbf{Paiment:}\\
      \\
      \ding{114} Comptant\\
      \ding{114} Ch�que\\
      \ding{114} Carte de cr�dit\\
      \\
      Nom: \hrulefill\\
      N$^{o}$: \hrulefill\\
      Expire fin: \hrulefill
    }}
  \hfill
  \fbox{\parbox[l][4cm]{.45\textwidth}{\textbf{Cadre r�serv� � la soci�t�:}}}

  \rule{\textwidth}{1mm}

  \@footer}

\endinput

%% facture.cls ends here.