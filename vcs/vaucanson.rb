class Vcs

  # See http://rubyforge.org/projects/vcs
  # and http://vcs.rubyforge.org

  protocol_version '0.1'

  def vcn_commit! ( *args )

    common_commit! "<%= rev %> <%= title %>", *args  do |subject|
      mail! :to => %w[vaucanson-patches@lrde.epita.fr], :subject => subject
    end

  end
  alias_command   :vcnci, :vcn_commit
  default_commit :vcn_commit

end # class Vcs
