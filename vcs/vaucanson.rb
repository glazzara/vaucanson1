class Vcs

  def vcn_commit! ( s, *args )

    common_commit!(*args) do |rev|
      news!(:groups => ['lrde.vaucanson.patches'],
            :subject => "[#{rev}] #{s}")
    end
  end
  alias_command :vcnci, :vcn_commit

end # class Vcs
