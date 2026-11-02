#include "veyron/Macro.hpp"
#include "veyron/WindowAnalyzer.hpp"
#include "veyron/Recorder.hpp"
#include "veyron/Replay.hpp"
#include "veyron/FormatIO.hpp"
#include <cassert>
#include <cmath>
#include <cstdio>
#include <vector>
int main() {
    const auto bands=veyron::WindowAnalyzer::defaultBands();
    assert(bands.size()==9 && bands.front().colorRGB==0xF04B68);
    assert(veyron::WindowAnalyzer::findBand(bands,1)==0);
    assert(veyron::WindowAnalyzer::findBand(bands,3)==2);
    assert(veyron::WindowAnalyzer::findBand(bands,24)==8);
    std::vector<veyron::MeasuredClick> sample={{10,1,false},{20,3,false},{30,8,false},{40,-1,false}};
    auto stats=veyron::WindowAnalyzer::summarize(sample,bands);
    assert(stats.measured==3 && stats.unknown==1 && stats.minimumFrames==1 && stats.maximumFrames==8);
    assert(std::abs(stats.averageFrames-4.0)<0.001);
    assert(veyron::WindowAnalyzer::toneFrequencyHz(1)<veyron::WindowAnalyzer::toneFrequencyHz(24));

    veyron::Recorder recorder; veyron::MacroMetadata meta; meta.tickRate=240;
    assert(recorder.begin(meta,100)); assert(recorder.record(1,false,true,105));
    assert(recorder.record(1,false,false,106)); auto captured=recorder.stop();
    assert(captured && captured->inputs.size()==2 && captured->inputs[0].frame==5);
    assert(veyron::exportVpr(*captured,"veyron-test.vpr").ok);
    veyron::Macro imported; assert(veyron::importVpr("veyron-test.vpr",imported).ok);
    assert(imported.inputs.size()==2 && imported.inputs[1].frame==6); std::remove("veyron-test.vpr");

    veyron::ReplayScheduler replay; assert(replay.load(*captured)); replay.start();
    assert(replay.advanceTo(5)==1); assert(replay.advanceTo(6)==1);
    assert(replay.state()==veyron::ReplayState::Finished);
    return 0;
}
