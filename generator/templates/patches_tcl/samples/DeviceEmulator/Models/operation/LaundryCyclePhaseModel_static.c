static Array_LaundryCyclePhase_CyclePhaseDescriptor* getPhases(void)
{
    static Array_LaundryCyclePhase_CyclePhaseDescriptor s_phases;

    if (!s_phases.elems) {
        InitArray_LaundryCyclePhase_CyclePhaseDescriptor(&s_phases, 0);
        size_t i = 0;

        i = ExtendArray_LaundryCyclePhase_CyclePhaseDescriptor(&s_phases, 1);
        s_phases.elems[i].phase = 1;
        s_phases.elems[i].name = strdup("fill");
        s_phases.elems[i].description = strdup("Fill with water");

        i = ExtendArray_LaundryCyclePhase_CyclePhaseDescriptor(&s_phases, 1);
        s_phases.elems[i].phase = 2;
        s_phases.elems[i].name = strdup("wash");
        s_phases.elems[i].description = strdup("Wash the laundry");

        i = ExtendArray_LaundryCyclePhase_CyclePhaseDescriptor(&s_phases, 1);
        s_phases.elems[i].phase = 3;
        s_phases.elems[i].name = strdup("dry");
        s_phases.elems[i].description = strdup("Dry the laundry");

    }

    return &s_phases;
}
