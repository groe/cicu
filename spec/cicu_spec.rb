require 'cicu'

describe Cicu::Ruleset do
  describe "#new" do
    it "should raise ArgumentError if rules are invalid" do
      expect(proc { Cicu::Ruleset.new("?") }).to raise_exception(ArgumentError)
    end
    it "should raise TypeError if argument is not a string" do
      expect(proc { Cicu::Ruleset.new([123]) }).to raise_exception(TypeError)
    end
    it "should raise ArgumentError if rules are too long" do
      rules = "[normalization on] & " + 100_000.times.map { "a" }.join("<")
      expect(proc { Cicu::Ruleset.new(rules) }).to raise_exception(ArgumentError)
    end
    it "should create a ruleset if rules are not too long" do
      ruleset = Cicu::Ruleset.new("[normalization on] & a < a < a < a < a < a")
      expect(ruleset.sort_key("123")).to eq("\x14\x16\x18\x01\a\x01\a")
    end
    it "should create a ruleset" do
      ruleset = Cicu::Ruleset.new("[normalization on] & a")
      expect(ruleset.sort_key("123")).to eq("\x14\x16\x18\x01\a\x01\a")
    end
  end
  describe "#sort_key" do
    it "should raise TypeErrorif argument is not a string" do
      ruleset = Cicu::Ruleset.new("[normalization on] & b < a < c")
      expect(proc { ruleset.sort_key([123]) }).to raise_exception(TypeError)
    end
    it "should sort any array according to the rukes" do
      ary = %w( a b c ba bb bc )
      ruleset = Cicu::Ruleset.new("[normalization on] & b < a < c")
      sorted_ary = ary.sort_by { |el| ruleset.sort_key(el) }
      expect(sorted_ary).to eq(%w( b bb ba bc a c ))
    end
  end
end