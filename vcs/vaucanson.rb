class Vcs

  def vcn_commit! ( *args )

    common_commit!( "[<%= rev %>] <%= title %>", *args) do |subject|
      mail!(:to => %w[vaucanson-patches@lrde.epita.fr],
            :subject => subject)
    end

  end
  alias_command :vcnci, :vcn_commit

end # class Vcs
