# -*- coding: utf-8 -*-

class PointData

  def initialize(t, n, x, y)
    @t = t
    @n = n
    @x = x
    @y = y
  end

  attr_accessor:t
  attr_reader:n
  attr_reader:x
  attr_reader:y
end

if(ARGV.length == 0) then
  puts "error need filename"
  exit 1
end

filename = ARGV[0]

if not File.exist?(filename) then
  puts filename + " does not exist"
  exit 1
end

dataset = Array.new(){Array.new}

open(filename) do |file|
  file.each do |s|
    #puts s
    m = s.match(/.*(\d\d):(\d\d):(\d\d)\.(\d\d\d)\s.*\((\d\d),\s([\d\.]*),\s*([\d\.]*)\)/)
    hour=m[1].to_i
    min=m[2].to_i
    sec=m[3].to_i
    ms=m[4].to_i
    n=m[5].to_i
    x=m[6].to_f
    y=m[7].to_f
    #puts "#{hour}:#{min}:#{sec}.#{ms} (#{n},#{x},#{y})"
    totalMs = hour * 60 * 60 * 1000 + 
              min  * 60 * 1000 +
              sec  * 1000 +
              ms
    #puts totalMs
    array=dataset[n]
    if(array == nil) then
      array=Array.new
    end
    array.push(PointData.new(totalMs,n,x,y))
    dataset[n]=array
  end

  dataset.each{|data|
    minT=data[0].t
    data.each {|point|
      point.t -= minT
      #puts "#{point.n} #{point.t} #{point.x} #{point.y}"     
    }
  }
end

counter = 0;
dataset.each do |data|
  filename = counter.to_s + ".dat"
  open(filename,"w"){|file|
    data.each do |point|
      file.write("#{point.t},#{point.x},#{point.y}\n")
    end
  }
  counter+=1
end
