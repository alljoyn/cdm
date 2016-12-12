static Array_DishWashingCyclePhase_CyclePhaseDescriptor* getPhases(void)
{
    static Array_DishWashingCyclePhase_CyclePhaseDescriptor s_phases;

    if (!s_phases.elems) {
        InitArray_DishWashingCyclePhase_CyclePhaseDescriptor(&s_phases, 0);
        size_t i = 0;

        i = ExtendArray_DishWashingCyclePhase_CyclePhaseDescriptor(&s_phases, 1);
        s_phases.elems[i].phase = 1;
        s_phases.elems[i].name = strdup("fill");
        s_phases.elems[i].description = strdup("Fill with water");

        i = ExtendArray_DishWashingCyclePhase_CyclePhaseDescriptor(&s_phases, 1);
        s_phases.elems[i].phase = 2;
        s_phases.elems[i].name = strdup("wash");
        s_phases.elems[i].description = strdup("Wash the dishes");

        i = ExtendArray_DishWashingCyclePhase_CyclePhaseDescriptor(&s_phases, 1);
        s_phases.elems[i].phase = 3;
        s_phases.elems[i].name = strdup("dry");
        s_phases.elems[i].description = strdup("Dry the dishes");

    }

    return &s_phases;
}
