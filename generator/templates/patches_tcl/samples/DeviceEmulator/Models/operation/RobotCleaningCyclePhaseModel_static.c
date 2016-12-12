static Array_RobotCleaningCyclePhase_CyclePhaseDescriptor* getPhases(void)
{
    static Array_RobotCleaningCyclePhase_CyclePhaseDescriptor s_phases;

    if (!s_phases.elems) {
        InitArray_RobotCleaningCyclePhase_CyclePhaseDescriptor(&s_phases, 0);
        size_t i = 0;

        i = ExtendArray_RobotCleaningCyclePhase_CyclePhaseDescriptor(&s_phases, 1);
        s_phases.elems[i].phase = 1;
        s_phases.elems[i].name = strdup("seek");
        s_phases.elems[i].description = strdup("Seek some dirt");

        i = ExtendArray_RobotCleaningCyclePhase_CyclePhaseDescriptor(&s_phases, 1);
        s_phases.elems[i].phase = 2;
        s_phases.elems[i].name = strdup("suck");
        s_phases.elems[i].description = strdup("Such it up");
    }

    return &s_phases;
}
