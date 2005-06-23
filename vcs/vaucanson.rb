class Vcs

  def vcn_commit! ( s, *args )

    common_commit!(*args) do |rev|
      mail!(:to => %w[vaucanson-patches@lrde.epita.fr],
            :subject => "[#{rev}] #{s}")
    end
  end
  alias_command :vcnci, :vcn_commit

end # class Vcs
