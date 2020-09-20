import { ComponentFixture, TestBed } from '@angular/core/testing';

import { HOMEPAGEComponent } from './home-page.component';

describe('HOMEPAGEComponent', () => {
  let component: HOMEPAGEComponent;
  let fixture: ComponentFixture<HOMEPAGEComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ HOMEPAGEComponent ]
    })
    .compileComponents();
  });

  beforeEach(() => {
    fixture = TestBed.createComponent(HOMEPAGEComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
